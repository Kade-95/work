import operator
import requests
from bs4 import BeautifulSoup


def GetWords(url):
    word_list = list()
    response = requests.get(url).text
    soup = BeautifulSoup(response, 'html.parser')
    for link in soup.findAll('a'):
        content = link.string
        if content is not None:
            word = content.lower().split()
            for each_word in word:
                word_list.append(each_word)
    clean_word(word_list)


def clean_word(word_list):
    clean_word_list = list()
    special_characters = '~`!@#$%^&*()_-+=\\|}{:;"\'/?.>,<';
    for word in word_list:
        for i in range(0, len(special_characters)):
            word = word.replace(special_characters[i], '')
        if len(word) > 0:
            clean_word_list.append(word)
    make_dictionary(clean_word_list)


def make_dictionary(clean_word_list):
    mydict = dict()
    for word in clean_word_list:
        if word in mydict:
            mydict[word] += 1
        else:
            mydict[word] = 1

    for key, value in sorted(mydict.items(), key=operator.itemgetter(1)):
        print(key+' : '+str(value))


GetWords('https://www.youtube.com/channel/UC0ZTPkdxlAKf-V33tqXwi3Q/playlists?disable_polymer=1')