import asoka as a
from Service.AType import *


Person = create_class('Person', (),
                      structure=(
                          Field('name', a.types.str, (True, True)),
                          Field('age', a.types.int, (True, True)),
                          Field('rating', a.types.float, (True, True)),
                          Field('friends', a.types.list),
                          Field('loving', 'Person')
                      ),
                      mode=Mode(DbProfile(name='tests.db', table='persons'))
                      )


if __name__ == '__main__':
    person = Person()

    person.setName('Вадим')
    person.setAge(24)
    person.setRating(3.6)
    person.friends.append('Саня')
    person.friends.append('Антон')
    person.friends.append('Женя')

    print(f'Name: {person.getName()}')
    print(f'Age: {person.getAge()}')
    print(f'Rating: {person.getRating()}')
    print(person.friends)
