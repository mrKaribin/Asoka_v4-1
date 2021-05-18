import kivy
import random
from Service.Global import *
from Types.File import File

kivy.require('2.0.0')
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.uix.gridlayout import GridLayout
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.button import Button
from kivy.uix.label import Label
from kivy.uix.image import Image
from kivy.properties import StringProperty


class FilterClosed(BoxLayout):
    pass


class FilterOpened(BoxLayout):
    pass


class IconLabel(Label):
    pass


class FileTag(Label):

    def __init__(self, name, **kwargs):
        super().__init__(**kwargs)
        self.name = name

    name = StringProperty('')


class FilePreview(BoxLayout):

    def __init__(self, file: File, **kwargs):
        super().__init__(**kwargs)
        self.file = file
        self.header = file.getHeader()
        self.source = type_to_icon.get(file.getType())
        layout = self.ids.tags_layout
        for i in range(random.randint(0, 10)):
            layout.add_widget(FileTag(f'tag{random.randint(1, 1000)}'))

    header = StringProperty('')
    source = StringProperty('')


class SearchScreen(Screen):

    def __init__(self, **kw):
        super().__init__(**kw)
        self.filter_is_open = False

    def search_clicked(self):
        text = self.ids.search_input.text
        layout = self.ids.result_layout
        layout.clear_widgets()
        for i in range(25):
            file = File()
            file.setHeader("Уникальный заголовок")
            file.setType(random.randint(1, 5))
            layout.add_widget(FilePreview(file))

    def filter_clicked(self):
        lay = self.ids.filter_layout
        lay.clear_widgets()
        if self.filter_is_open:
            lay.add_widget(FilterClosed())
            self.filter_is_open = False
        else:
            lay.add_widget(FilterOpened())
            self.filter_is_open = True

    def back_clicked(self):
        self.manager.current = 'main'
