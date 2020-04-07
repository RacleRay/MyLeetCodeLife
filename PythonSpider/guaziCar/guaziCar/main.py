import re

import execjs
import requests
from scrapy import cmdline

from guaziCar.mongoDB import mongo
from guaziCar.settings import USER_AGENT, DEFAULT_REQUEST_HEADERS


def gen_init_task(url, city_to_crawl):
    DEFAULT_REQUEST_HEADERS['User-Agent'] = USER_AGENT
    header = DEFAULT_REQUEST_HEADERS
    response = requests.get(url=url, headers=header)
    response.encoding = 'utf-8'
    if '正在打开中,请稍后' in response.text:
        value_search = re.compile(r"anti\('(.*?)','(.*?)'\);")
        string = value_search.search(response.text).group(1)
        key = value_search.search(response.text).group(2)
        with open('extracted_js.js', 'r', encoding='utf-8') as f:
            f_read = f.read()
        js = execjs.compile(f_read)
        js_return = js.call('anti', string, key)
        cookie_value = 'antipas=' + js_return
        header['Cookie'] = cookie_value

        response_second = requests.get(url=url, headers=header)
        response.encoding = 'utf-8'
        city_search = re.compile(r'"domain":"(\w+?)".?"name":"(.+?)"')
        city_list = city_search.findall(response_second.text)
        brand_search = re.compile(r'href="\/www\/(.*?)\/c-1/#bread"\s+>(.*?)</a>')
        brand_list = brand_search.findall(response_second.text)
        for city in city_list:
            hanzi_city = city[1].encode('utf-8').decode('unicode_escape')
            if hanzi_city == city_to_crawl:
                for brand in brand_list:
                    info = {}
                    info['task_url'] = 'https://www.guazi.com/' + city[0] + '/' + brand[0] + '/' + 'o1i7'
                    info['city_name'] = hanzi_city
                    info['brand_name'] = brand[1]
                    info['item_type'] = 'cars_page'
                    mongo.save_task(info, 'guazi_task')


if __name__ == "__main__":
    url = 'https://www.guazi.com/www/buy'
    city_to_crawl = '成都'
    gen_init_task(url, city_to_crawl)
    cmdline.execute("scrapy crawl carCrawl".split())