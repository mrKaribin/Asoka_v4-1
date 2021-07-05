import kivy

from Service import Global
from Widgets.SearchScreen import SearchScreen
from Widgets.AddScreen import AddScreen

kivy.require(Global.current_kivy_version)
from kivy.app import App
from kivy.lang import Builder
from kivy.core.window import Window
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.uix.boxlayout import BoxLayout


from os import listdir
kv_path = './Widgets/kv/'
for kv in listdir(kv_path):
    Builder.load_file(kv_path+kv)


class MainScreen(Screen):

    def search_clicked(self):
        self.manager.switch_to(Context.search_screen)

    def add_clicked(self):
        self.manager.switch_to(Context.add_screen)

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


class Context(BoxLayout):

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        if Global.currentOs == 'win32':
            Window.size = (400, 580)
        Window.clearcolor = (250, 238, 221, 225)
        self.title = 'Менеджер задач'

        self.manager = ScreenManager()
        self.manager.switch_to(self.main_screen)
        self.add_widget(self.manager)

    main_screen = MainScreen(name='main')
    search_screen = SearchScreen(name='search')
    add_screen = AddScreen(name='add')


class MainWindow(App):

    def build(self):
        return Context()