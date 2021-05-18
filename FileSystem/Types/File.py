import sys
from Service import Global
sys.path.append(Global.PyAsoka_Path)
sys.path.append(Global.PyAsoka_Service_Path)
import asoka
from AsokaType import *


class File(AsokaType):

    def __init__(self, id = asoka.nullInt):
        super().__init__(
            id=id,
            structure=Structure()
                .create_field('header', FieldType.string)
                .create_field('type', FieldType.int)
                .create_field('blocks', FieldType.objects_array)
                .getMap(),
            database=databaseConfig('filesystem.db', 'files'),
            environment=environmentConfig(__file__)
        )

    def getHeader(self):
        return self.get('header')

    def getType(self):
        return self.get('type')

    def getBlocks(self):
        return self.get('blocks')

    def setHeader(self, header):
        self.set('header', header)

    def setType(self, type):
        self.set('type', type)

    def setBlocks(self, blocks):
        self.set('blocks', blocks)
