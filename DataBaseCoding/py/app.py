import os
import sys
import time

from colorama import Fore, Style, init
from getpass import getpass

from service.user_service import UserService
from service.news_service import NewsService
from service.role_service import RoleService
from service.type_service import TypeService

init()
__user_service = UserService()
__news_service = NewsService()
__role_service = RoleService()
__type_service = TypeService()


def signIn():
    username = input("\n\t用户名:")
    password = getpass("\n\t密码:")
    result = __user_service.login(username, password)
    return result, username


def show_login():
    os.system('cls')
    print(Fore.LIGHTBLUE_EX, "\n\t==================")
    print(Fore.LIGHTBLUE_EX, "\n\t欢迎使用新闻管理系统")
    print(Fore.LIGHTBLUE_EX, "\n\t==================")
    print(Fore.LIGHTGREEN_EX, "\n\t1.登陆系统")
    print(Fore.LIGHTGREEN_EX, "\n\t2.退出系统")
    print(Style.RESET_ALL)


def show_page_list(page):
    os.system("cls")
    count_page = __news_service.search_unreview_count_page()
    result = __news_service.search_unreview_list(page)
    for index in range(len(result)):
        one = result[index]
        print(Fore.LIGHTBLUE_EX, "\n\t%d\t%s\t%s\t%s" % (index + 1, one[1], one[2], one[3]))
    print(Fore.LIGHTBLUE_EX, "\n\t-------------------")
    print(Fore.LIGHTBLUE_EX, "\n\t%d/%d" % (page, count_page))
    print(Fore.LIGHTBLUE_EX, "\n\t-------------------")
    print(Fore.LIGHTRED_EX, "\n\tback.返回上一层")
    print(Fore.LIGHTRED_EX, "\n\tprev.上一页")
    print(Fore.LIGHTRED_EX, "\n\tnext.下一页")
    print(Style.RESET_ALL)
    return result, count_page


def deceive_news():
    page = 1
    while True:
        result, count_page = show_page_list(page)
        opt = input("\n\t输入操作编号:")
        if opt == "back":
            break
        elif opt == "prev" and page > 1:
            page -= 1
        elif opt == "next" and page < count_page:
            page += 1
        elif int(opt) >= 1 and int(opt) <= 10:
            news_id = result[int(opt) - 1][0]
            __news_service.update_unreview_news(news_id)
            to_check = __news_service.search_cache(news_id)

            title = to_check[0]
            username = to_check[1]
            type = to_check[2]
            content_id = to_check[3]
            is_top = to_check[4]
            create_time = str(to_check[5])

            content = __news_service.search_content_by_id(content_id)
            # 推送到redis
            __news_service.cache_news(news_id, title, username, type, content, is_top, create_time)


def delete_news():
    page = 1
    while True:
        result, count_page = show_page_list(page)
        opt = input("\n\t输入操作编号:")
        if opt == "back":
            break
        elif opt == "prev" and page > 1:
            page -= 1
        elif opt == "next" and page < count_page:
            page += 1
        elif int(opt) >= 1 and int(opt) <= 10:
            news_id = result[int(opt) - 1][0]
            __news_service.delete_by_id(news_id)
            __news_service.delete_cache(news_id)


def add_user():
    os.system("cls")
    username = input("\n\t用户名:")
    password = getpass("\n\t密码:")
    repassword = getpass("\n\t重复密码:")
    checked = False
    if password != repassword:
        print("\n\t两次密码不一致(3秒自动返回)")
        time.sleep(3)
        checked = add_user()
    if checked:
        return True
    email = input("\n\t邮箱:")
    result = __role_service.search_list()
    for index in range(len(result)):
        one = result[index]
        print(Fore.LIGHTBLUE_EX, "\n\t%d.%s" % (index + 1, one[1]))
    print(Style.RESET_ALL)
    opt = input("\n\t角色编号:")
    role_id = result[int(opt) - 1][0]

    __user_service.insert(username, password, email, role_id)
    print("\n\t保存成功(3秒自动返回)")
    time.sleep(3)

    return True


def show_page_user(page):
    os.system("cls")
    count_page = __user_service.search_count_page()
    result = __user_service.search_list(page)
    for index in range(len(result)):
        one = result[index]
        print(Fore.LIGHTBLUE_EX,
              "\n\t%d\t%s\t%s" % (index + 1, one[1], one[2]))
    print(Fore.LIGHTBLUE_EX, "\n\t-------------------")
    print(Fore.LIGHTBLUE_EX, "\n\t%d/%d" % (page, count_page))
    print(Fore.LIGHTBLUE_EX, "\n\t-------------------")
    print(Fore.LIGHTRED_EX, "\n\tback.返回上一层")
    print(Fore.LIGHTRED_EX, "\n\tprev.上一页")
    print(Fore.LIGHTRED_EX, "\n\tnext.下一页")
    print(Style.RESET_ALL)
    return result, count_page


def modify_user():
    page = 1
    while True:
        result, count_page = show_page_user(page)
        opt = input("\n\t输入操作编号:")
        if opt == "back":
            break
        elif opt == "prev" and page > 1:
            page -= 1
        elif opt == "next" and page < count_page:
            page += 1
        elif int(opt) >= 1 and int(opt) <= 10:
            os.system("cls")
            user_id = result[int(opt) - 1][0]
            username = input("\n\t新用户名:")
            password = getpass("\n\t新密码:")
            repassword = getpass("\n\t再次输入密码:")
            if password != repassword:
                print(Fore.LIGHTRED_EX, "\n\t两次密码不一致(3秒自动返回)")
                print(Style.RESET_ALL)
                time.sleep(3)
                break
            email = input("\n\t新邮箱:")
            result = __role_service.search_list()
            for index in range(len(result)):
                one = result[index]
                print(Fore.LIGHTBLUE_EX, "\n\t%d.%s" % (index + 1, one[1]))
            print(Style.RESET_ALL)
            opt = input("\n\t角色编号:")
            role_id = result[int(opt) - 1][0]
            opt = input("\n\t是否保存(Y/N)")
            if opt == "Y" or opt == "y":
                __user_service.update(user_id, username, password, email, role_id)
                print("\n\t保存成功(3秒自动返回)")
                time.sleep(3)


def delete_user():
    page = 1
    while True:
        result, count_page = show_page_user(page)
        opt = input("\n\t输入操作编号:")
        if opt == "back":
            break
        elif opt == "prev" and page > 1:
            page -= 1
        elif opt == "next" and page < count_page:
            page += 1
        elif int(opt) >= 1 and int(opt) <= 10:
            os.system("cls")
            user_id = result[int(opt) - 1][0]
            __user_service.delete_by_id(user_id)
            print("\n\t删除成功(3秒自动返回)")
            time.sleep(3)


def show_manager():
    print(Fore.LIGHTGREEN_EX, "\n\t1.新闻管理")
    print(Fore.LIGHTGREEN_EX, "\n\t2.用户管理")
    print(Fore.LIGHTRED_EX, "\n\tback.退出登陆")
    print(Fore.LIGHTRED_EX, "\n\texit.退出系统")
    print(Style.RESET_ALL)


def show_news_manage():
    os.system("cls")
    print(Fore.LIGHTGREEN_EX, "\n\t1.审批新闻")
    print(Fore.LIGHTGREEN_EX, "\n\t2.删除新闻")
    print(Fore.LIGHTRED_EX, "\n\tback.返回上一层")
    print(Style.RESET_ALL)


def show_user_manage():
    os.system("cls")
    print(Fore.LIGHTGREEN_EX, "\n\t1.添加用户")
    print(Fore.LIGHTGREEN_EX, "\n\t2.修改用户")
    print(Fore.LIGHTGREEN_EX, "\n\t3.删除用户")
    print(Fore.LIGHTRED_EX, "\n\tback.返回上一层")
    print(Style.RESET_ALL)


def show_news_edit():
    print(Fore.LIGHTGREEN_EX, "\n\t1.发表新闻")
    print(Fore.LIGHTGREEN_EX, "\n\t2.编辑新闻")
    print(Fore.LIGHTRED_EX, "\n\tback.退出登陆")
    print(Fore.LIGHTRED_EX, "\n\texit.退出系统")
    print(Style.RESET_ALL)


def add_news(username):
    os.system("cls")
    title = input("\n\t新闻标题:")
    userid = __user_service.search_userid(username)
    types = __type_service.search_list()
    for index in range(len(types)):
        one = types[index]
        print(Fore.LIGHTBLUE_EX, "\n\t%d.%s" % (index + 1, one[1]))
    print(Style.RESET_ALL)
    opt = input("\n\t类型编号:")
    type_id = types[int(opt) - 1][0]

    file_path = input("\n\t输入文件路径:")
    file = open(file_path, 'r')
    content = file.read()
    file.close()

    is_top = input("\n\t置顶级别(0-5):")
    is_commite = input("\n\t是否提交(Y/N):")
    if is_commite == "Y" or is_commite == "y":
        __news_service.insert(title, userid, type_id, content, is_top)
        print("\n\t保存成功(1秒自动返回)")
        time.sleep(1)


def show_news_list(page):
    os.system("cls")
    count_page = __news_service.search_count_page()
    result = __news_service.search_list(page)
    for index in range(len(result)):
        one = result[index]
        print(Fore.LIGHTBLUE_EX, "\n\t%d\t%s\t%s\t%s" % (index + 1, one[1], one[2], one[3]))
    print(Fore.LIGHTBLUE_EX, "\n\t-------------------")
    print(Fore.LIGHTBLUE_EX, "\n\t%d/%d" % (page, count_page))
    print(Fore.LIGHTBLUE_EX, "\n\t-------------------")
    print(Fore.LIGHTRED_EX, "\n\tback.返回上一层")
    print(Fore.LIGHTRED_EX, "\n\tprev.上一页")
    print(Fore.LIGHTRED_EX, "\n\tnext.下一页")
    print(Style.RESET_ALL)
    return result, count_page


def update_news(change_content=False):
    page = 1
    while True:
        result, count_page = show_news_list(page)
        opt = input("\n\t输入操作编号:")
        if opt == "back":
            break
        elif opt == "prev" and page > 1:
            page -= 1
        elif opt == "next" and page < count_page:
            page += 1
        elif int(opt) >= 1 and int(opt) <= 10:
            os.system("cls")
            news_id = result[int(opt) - 1][0]
            one_news = __news_service.search_by_id(news_id)

            title = one_news[0]
            type = one_news[1]
            is_top = one_news[2]
            content_id = one_news[3]

            print("\n\t新闻原标题: %s" % (title))
            new_title = input("\n\t新标题:")
            print("\n\t原类型: %s" % (type))
            types = __type_service.search_list()
            for index in range(len(types)):
                one = types[index]
                print(Fore.LIGHTBLUE_EX, "\n\t%d.%s" % (index + 1, one[1]))
            print(Style.RESET_ALL)
            opt = input("\n\t类型编号:")
            type_id = types[int(opt) - 1][0]

            change = input("\n\t是否更改新闻内容(Y/N):")
            change_content = True if change.lower() == "y" else False

            if change_content:
                path = input("\n\t输入内容路径:")
                file = open(path, "r")
                content = file.read()
                file.close()
            else:
                content = __news_service.search_content_by_id(content_id)

            print("\n\t原置顶级别: %s" % (is_top))
            new_is_top = input("\n\t置顶级别(0-5):")
            is_commite = input("\n\t是否提交？(Y/N):")
            if is_commite == "Y" or is_commite == "y":
                __news_service.update(news_id, new_title, type_id, content, new_is_top)
                print("\n\t保存成功(1秒自动返回)")
                time.sleep(1)


def main():
    while True:
        show_login()
        opt = input("\n\t输入操作编号:")
        if opt == "1":
            result, username = signIn()
            if result is True:
                role = __user_service.search_user_role(username)
                while True:
                    os.system("cls")
                    if role == "新闻编辑":
                        show_news_edit()
                        opt = input("\n\t输入操作编号:")
                        if opt == "1":
                            add_news(username)
                        elif opt == "2":
                            update_news()
                        elif opt == "back":
                            break
                        elif opt == "exit":
                            sys.exit(0)
                    elif role == "管理员":
                        show_manager()
                        opt = input("\n\t输入操作编号:")
                        if opt == "1":
                            while True:
                                show_news_manage()
                                opt = input("\n\t输入操作编号:")
                                if opt == "1":
                                    deceive_news()
                                elif opt == "2":
                                    delete_news()
                                elif opt == "back":
                                    break
                        elif opt == "2":
                            while True:
                                show_user_manage()
                                opt = input("\n\t输入操作编号:")
                                if opt == "back":
                                    break
                                elif opt == "1":
                                    add_user()
                                elif opt == "2":
                                    modify_user()
                                elif opt == "3":
                                    delete_user()
                        elif opt == 'back':
                            break
                        elif opt == 'exit':
                            sys.exit(0)
            else:
                print("\n\t登录失败(3秒自动返回)")
                time.sleep(3)
        elif opt == "2":
            sys.exit(0)


if __name__ == "__main__":
    main()
