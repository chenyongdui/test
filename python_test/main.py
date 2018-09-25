# coding=utf-8

import requests
import urllib
import json
import sys 
import os
#reload(sys) 
#sys.setdefaultencoding( "utf-8")


from selenium import webdriver
from pyvirtualdisplay import Display  


os.system("ps -ef | grep chrome | grep -v grep | awk '{print $2}' | xargs kill -9")

display = Display(visible=0, size=(800,600))  
display.start()  
  
  
driver = webdriver.Chrome()  
driver.get("https://www.toutiao.com/c/user/6516515491/#mid=1562355680524289")  
#driver.find_element_by_xpath("./*//input[@id='kw']").send_keys("赤潮")  
#driver.find_element_by_xpath("./*//input[@id='su']").click()  
#print(driver.page_source)  


#item = driver.find_element_by_class_name('relatedFeed')
items = driver.find_elements_by_class_name('item-inner')

for item in items:
	item_title = item.find_element_by_class_name('title')
	#item_read = item.find_element_by_class_name('lbtn')
	try:
		item_read = item.find_element_by_xpath("./*//a[@ga_event='article_read_count']")
	except:
		item_read = item.find_element_by_xpath("./*//a[@ga_event='video_play_count']")
	item_comment = item.find_element_by_class_name('comment')
	print(item_title.text.strip(' '))
	print(item_read.text.strip(' '))
	print(item_comment.text.strip(' '))

#print(item.text)

'''fd = open('aaa.html', 'w+')
fd.write(driver.page_source)
fd.close()'''

'''browser = webdriver.Chrome()

browser.get("https://www.toutiao.com/i6482646112527188494/")
print(browser.page_source)
browser.close() 
'''

'''url = 'https://www.toutiao.com/i6482646112527188494/'

data = urllib.urlopen(url).read().decode("UTF-8")
print data

fd = open('aaa.html', 'w+')
fd.write(data)
fd.close()'''