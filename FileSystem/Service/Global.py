

PyAsoka_Path = '../PyAsoka'
PyAsoka_Service_Path = '../PyAsoka/Service'
currentUIType = 0


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