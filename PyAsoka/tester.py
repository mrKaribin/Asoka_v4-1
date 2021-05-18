import random

from Service.AsokaType import *
from Service.Database.SqLite import SqLite as Database
import os
import json


class Numbericon(AsokaType):

    def __init__(self, id=asoka.nullInt):
        super().__init__(
            id=id,
            structure=Structure()
                .create_field('name', FieldType.string)
                .create_field('number1', FieldType.int)
                .create_field('number2', FieldType.int)
                .getMap(),
            database=databaseConfig('tests.db', 'numbericon'),
            environment=environmentConfig(__file__)
        )

    def setData(self, name, num1, num2):
        self.set('name', name)
        self.set('number1', num1)
        self.set('number2', num2)


class Location(AsokaType):

    def __init__(self, id=asoka.nullInt):
        super().__init__(
            id=id,
            structure=Structure()
                .create_field('country', FieldType.string)
                .create_field('city', FieldType.string)
                .getMap(),
            database=databaseConfig('tests.db', 'locations'),
            environment=environmentConfig(__file__)
        )

    def setData(self, country, city):
        self.set('country', country)
        self.set('city', city)


class Profile(AsokaType):

    def __init__(self, id=asoka.nullInt):
        super().__init__(
            id=id,
            structure=Structure()
                .create_field('name', FieldType.string)
                .create_field('age', FieldType.int)
                .create_field('male', FieldType.bool)
                .create_field('location', FieldType.object)
                .create_field('numericons', FieldType.objects_array)
                .getMap(),
            database=databaseConfig('tests.db', 'profiles'),
            environment=environmentConfig(__file__)
        )

    def setData(self, name, age, male, loc):
        self.set('name', name)
        self.set('age', age)
        self.set('male', male)
        self.set('location', loc)


if __name__ == '__main__':
    while True:
        print("Testing mode started:")
        command = input()

        words = command.split(' ')
        if len(words) > 1 and words[0] == 'testing':
            if len(words) > 2 and words[1] == 'AsokaType':
                if words[2] in ('basic', 'all'):
                    # testing AsokaType basic
                    location = Location()
                    location.setData('Россия', 'Санкт-Петербург')
                    profile = Profile()
                    profile.setData('Демьян', 10, True, location)
                    for i in range(5):
                        numericon = Numbericon()
                        numericon.setData(
                            'Уникальное имя',
                            random.randint(0, 100),
                            random.randint(0, 100)
                        )
                        profile.get('numericons').append(numericon)

                    profile.save()
                    id = profile.getId()

                    profile = Profile()
                    profile.load(id)
                    print(f"Имя: {profile.get('name')}")
                    print(f"Возраст: {profile.get('age')}")
                    print(f"Пол: {profile.get('male')}")
                    print(f"Страна: {profile.get('location').get('country')}")
                    print(f"Город: {profile.get('location').get('city')}")
                    print(f"Нумериконы:")
                    for num in profile.get('numericons'):
                        print(f"Имя: {num.get('name')}")
                        print(f"Номер 1: {num.get('number1')}")
                        print(f"Номер 2: {num.get('number2')}")
