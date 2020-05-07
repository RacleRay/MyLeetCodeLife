import time
import pymongo
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from lxml import etree
from selenium.webdriver.chrome.options import Options


class MongoDB:
    def __init__(self, host, username, password):
        self.__client = pymongo.MongoClient(host=host, port=27017)
        self.__client.admin.authenticate(username, password)

    def insert(self, items):
        try:
            self.__client['jobInfoSelenium']['jobInfoCollection'].insert_many(
                items)
        except Exception as e:
            print(e)


class WebDriver:
    def __init__(self):
        options = Options()
        options.add_argument('--headless')
        self.driver = webdriver.Chrome(chrome_options=options)
        self.driver.maximize_window()
        self.mongoDb = MongoDB(host='192.168.1.68',
                               username="rootsu", password="123456")

    def crawlJob(self, url):
        self.driver.get(url)
        if WebDriverWait(self.driver, 5, 0.5).until(
                EC.presence_of_element_located((By.ID, 'kwdselectid'))):
            input_keyword = input('请输入要查找的岗位信息: ')
            self.driver.find_element_by_xpath(
                "//p[@class='ipt']/input").send_keys(input_keyword)
            self.driver.find_element_by_xpath(
                "//button[@class='p_but']").click()
            if WebDriverWait(self.driver, 5, 0.5).until(
                    EC.presence_of_element_located((By.ID, 'resultList'))):
                count = 1
                while count <= 10:
                    time.sleep(3)
                    self.parse(self.driver.page_source)
                    if self.driver.find_element_by_xpath("//li[@class='bk'][2]/a").text == '下一页':
                        self.driver.find_element_by_xpath(
                            "//li[@class='bk'][2]/a").click()
                        count += 1
                    else:
                        break

    def parse(self, page_source):
        html = etree.HTML(page_source)
        all_div = html.xpath("//div[@id='resultList']//div[@class='el']")
        items = []
        for item in all_div:
            info = {}
            # item下的xpath语句, 需要添加./
            info['job_name'] = item.xpath("./p/span/a/@title")[0]
            info['company_name'] = item.xpath(
                ".//span[@class='t2']/a/@title")[0]
            info['company_address'] = item.xpath(
                ".//span[@class='t3']/text()")[0]
            try:
                info['money'] = item.xpath(".//span[@class='t4']/text()")[0]
            except IndexError:
                info['money'] = '工资缺失'
            info['date'] = item.xpath(".//span[@class='t5']/text()")[0]
            items.append(info)
        self.mongoDb.insert(items)


if __name__ == "__main__":
    crawler = WebDriver()
    init_url = "https://search.51job.com/list/000000,000000,0000,00,9,99,%2520,2,1.html"
    crawler.crawlJob(init_url)
