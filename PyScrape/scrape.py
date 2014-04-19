from bs4 import BeautifulSoup

import requests

url = 'http://services.runescape.com/m=hiscore/ranking?category_type=0&table=15&page='

def main():
	for x in xrange(3200, 4000):
		r = requests.get('http://' + url + x)

		data = r.text

		getNames(data)


def getNames(data):
	soup = BeautifulSoup(data)

	for link in soup.find_all('tr'):
		print(link.get('col2'))

if __name__ == "__main__":
	main();
