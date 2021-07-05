import io
import kivy
import random

from Service.Global import *
from Types.File import File

kivy.require(current_kivy_version)
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.core.image import Image as CoreImage
from kivy.properties import StringProperty, NumericProperty, ObjectProperty
from kivy.uix.floatlayout import FloatLayout
from kivy.uix.gridlayout import GridLayout
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.label import Label
from kivy.uix.popup import Popup


class TagEditDialog(BoxLayout):
    load = ObjectProperty(None)
    cancel = ObjectProperty(None)


class LoadDialog(BoxLayout):
    load = ObjectProperty(None)
    cancel = ObjectProperty(None)


class TagLabel(Label):

    def __init__(self, name, **kwargs):
        super().__init__(**kwargs)
        self.name = name

    name = StringProperty('')
    win_width = NumericProperty(0)
    win_height = NumericProperty(0)


class InputBlock(BoxLayout):
    def __init__(self, index: int, type: int, **kwargs):
        super().__init__(**kwargs)
        self.index = index
        self.type = type

    def getInput(self):
        return self.ids.input


class TextBlock(InputBlock):
    def __init__(self, index: int, type: int, **kwargs):
        super().__init__(index, type, **kwargs)


class ImageBlock(InputBlock):
    def __init__(self, index: int, type: int, texture, **kwargs):
        super().__init__(index, type, **kwargs)
        self.ids.input.texture = texture


class AddScreen(Screen):

    def __init__(self, **kw):
        super().__init__(**kw)
        self.current_index = 0

    def getIndex(self):
        self.current_index += 1
        return self.current_index

    def add_tag_clicked(self):
        layout = self.ids.tags_layout
        layout.add_widget(TagLabel('tag'))

    def add_image_clicked(self):
        content = LoadDialog(load = self.save_image, cancel = self.close_loader)
        self.popup = Popup(
            title = 'Выбор изображения',
            content = content,
            size_hint = (0.9, 0.9)
        )
        self.popup.open()
        print('Image added')

    def add_video_clicked(self):
        print('Video added')

    def add_audio_clicked(self):
        print('Audio added')

    def add_text_clicked(self):
        layout = self.ids.blocks_layout
        block = TextBlock(self.getIndex(), InfoType.text)
        layout.add_widget(block)
        print('Text added')

    def save_clicked(self):
        print('File saved')

    def close_loader(self):
        self.popup.dismiss()

    def save_image(self, path, filename):
        ext = filename[0].split('.')[1]
        path = path[0][1:]
        file_path = path + filename[0]
        # print(f'Файл: {file_path}\nРасширение: {ext}')
        data = io.BytesIO(open(file_path, "rb").read())
        image = CoreImage(data, ext=ext)
        layout = self.ids.blocks_layout
        block = ImageBlock(self.getIndex(), InfoType.image, image.texture)
        layout.add_widget(block)
        self.close_loader()

    def back_clicked(self):
        self.manager.switch_to(self.parent.parent.main_screen)
