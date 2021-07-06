import asoka as a
from Service.Console import *
from Service.AType import *


Person = create_class('Person', (),
                      structure=(
                          Field('name', a.types.str, (True, True)),
                          Field('gender', a.types.bool, (True, True)),
                          Field('age', a.types.int, (True, True)),
                          Field('rating', a.types.float, (True, True)),
                          Field('friends', a.types.list),
                          Field('loving', 'Person')
                      ),
                      mode=Mode(DbProfile(a.types.db.lang.sqlite, 'tests.db', table='persons'))
                      )


if __name__ == '__main__':
    person = Person()

    person.setName('Вадим')
    person.setGender(True)
    person.setAge(24)
    person.setRating(3.6)
    person.friends.append('Саня')
    person.friends.append('Антон')
    person.friends.append('Женя')

    comment(f'Name: {person.getName()}')
    comment(f'Gender: {person.getGender()}')
    comment(f'Age: {person.getAge()}')
    comment(f'Rating: {person.getRating()}')
    comment(person.friends)
    person.insert()
