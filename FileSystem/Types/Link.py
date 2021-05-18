import sys
from Service import Global
sys.path.append(Global.PyAsoka_Path)
sys.path.append(Global.PyAsoka_Service_Path)
import asoka
from AsokaType import *


class Link(AsokaType):

    def __init__(self, id = asoka.nullInt):
        super().__init__(
            id=id,
            structure=Structure()
                .create_field('file_id', FieldType.int)
                .create_field('tag_id', FieldType.int)
                .getMap(),
            database=databaseConfig('filesystem.db', 'links'),
            environment=environmentConfig(__file__)
        )

    def getFileId(self):
        return self.get('file_id')

    def getTagId(self):
        return self.get('tag_id')

    def setFileId(self, file_id):
        self.set('file_id', file_id)

    def setTagId(self, tag_id):
        self.set('tag_id', tag_id)
