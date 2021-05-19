import sys

PyAsoka_Path = '../PyAsoka'
PyAsoka_Service_Path = '../PyAsoka/Service'

currentUIType = 0
currentOs = sys.platform
current_kivy_version = '' 
if currentOs == 'win32':
	current_kivy_version = '2.0.0'
elif currentOs == 'linux':
	current_kivy_version ='1.11.1'


class UIType:
    linear = 1
    full_screen = 2


class InfoType:
    image = 1
    video = 2
    audio = 3
    text = 4
    page = 5


type_to_icon = {
    InfoType.image: './icons/image.png',
    InfoType.video: './icons/video.png',
    InfoType.audio: './icons/music.png',
    InfoType.text: './icons/text.png',
    InfoType.page: './icons/page.png'
}