import kivy
import random
from Service.Global import *
from Types.File import File

kivy.require(current_kivy_version)
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.properties import StringProperty, NumericProperty
from kivy.uix.gridlayout import GridLayout
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.label import Label


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
        print('Image added')

    def add_video_clicked(self):
        print('Video added')

    def add_audio_clicked(self):
        print('Audio added')

    def add_text_clicked(self):
        layout = self.ids.blocks_layout
        layout.add_widget(TextBlock(self.getIndex(), InfoType.text))
        print('Text added')

    def back_clicked(self):
        self.manager.current = 'main'

    def save_clicked(self):
        print('File saved')
