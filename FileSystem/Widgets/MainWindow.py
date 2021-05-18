import kivy
from Widgets.SearchScreen import SearchScreen
from Widgets.AddScreen import AddScreen

kivy.require('2.0.0')
from kivy.app import App
from kivy.lang import Builder
from kivy.core.window import Window
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.gridlayout import GridLayout
from kivy.uix.textinput import TextInput
from kivy.uix.image import Image
from kivy.uix.button import Button


from os import listdir
kv_path = './Widgets/kv/'
for kv in listdir(kv_path):
    Builder.load_file(kv_path+kv)


class MainScreen(Screen):

    def search_clicked(self):
        self.manager.current = 'search'

    def add_clicked(self):
        self.manager.current = 'add'

    def image_clicked(self):
        print('Clicked button "Image"')

    def video_clicked(self):
        print('Clicked button "Video"')

    def music_clicked(self):
        print('Clicked button "Music"')

    def page_clicked(self):
        print('Clicked button "Page"')

    def statistic_clicked(self):
        print('Clicked button "Statistic"')

    def random_clicked(self):
        print('Clicked button "Random"')


class MainWindow(App):

    def __init__(self, width, heigth, **kwargs):
        super().__init__(**kwargs)
        self.width, self.heigth = width, heigth

        Window.size = (width, heigth)
        Window.clearcolor = (250, 238, 221, 225)
        self.title = 'Менеджер задач'

        self.sm = ScreenManager()
        self.sm.add_widget(MainScreen(name='main'))
        self.sm.add_widget(SearchScreen(name='search'))
        self.sm.add_widget(AddScreen(name='add'))

    def build(self):
        return self.sm


