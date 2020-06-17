# coding: utf-8

import xml.etree.ElementTree as ET
import os

names_dict = {}
cnt = 0
f = open('./data/my_data/voc_names.txt', 'r').readlines()
for line in f:
    line = line.strip()
    names_dict[line] = cnt
    cnt += 1

train_path = 'train.txt'
val_path = 'val.txt'
test_path = 'test.txt'


def parse_xml(path):
    tree = ET.parse(path)
    img_name = path.split('/')[-1][:-4]
    
    height = tree.findtext("./size/height")
    width = tree.findtext("./size/width")

    objects = [img_name, width, height]

    for obj in tree.findall('object'):
        difficult = obj.find('difficult').text
        if difficult == '1':
            continue
        name = obj.find('name').text
        bbox = obj.find('bndbox')
        xmin = bbox.find('xmin').text
        ymin = bbox.find('ymin').text
        xmax = bbox.find('xmax').text
        ymax = bbox.find('ymax').text

        name = str(names_dict[name])
        objects.extend([name, xmin, ymin, xmax, ymax])
    if len(objects) > 1:
        return objects
    else:
        return None

test_cnt = 0
def gen_test_txt():
    global test_cnt
    f = open(test_path, 'w')

    images = os.listdir('data/my_data/testImg')

    for i, path in enumerate(images):
        if True:
            img_name = path.split('.')[0]
            xml_path = 'data/my_data/testAnn' + '/' + img_name + '.xml'
            objects = parse_xml(xml_path)
            if objects:
                objects[0] = 'data/my_data/'+'testImg' + '/' + img_name + '.png'
                if os.path.exists(objects[0]):
                    objects.insert(0, str(test_cnt))
                    test_cnt += 1
                    objects = ' '.join(objects) + '\n'
                    f.write(objects)
    f.close()

val_cnt = 0
def gen_val_txt():
    global val_cnt
    f = open(val_path, 'w')

    images = os.listdir('data/my_data/valImg')

    for i, path in enumerate(images):
        if True:
            img_name = path.split('.')[0]
            xml_path = 'data/my_data/valAnn' + '/' + img_name + '.xml'
            objects = parse_xml(xml_path)
            if objects:
                objects[0] = 'data/my_data/'+'valImg' + '/' + img_name + '.png'
                if os.path.exists(objects[0]):
                    objects.insert(0, str(val_cnt))
                    val_cnt += 1
                    objects = ' '.join(objects) + '\n'
                    f.write(objects)
    f.close()


train_cnt = 0
def gen_train_txt():
    global train_cnt
    f = open(train_path, 'w')    

    images = os.listdir('data/my_data/trainImg')

    for i, path in enumerate(images):
        if True:
            img_name = path.split('.')[0]
            xml_path = 'data/my_data/trainAnn' + '/' + img_name + '.xml'
            objects = parse_xml(xml_path)
            if objects:
                objects[0] = 'data/my_data/'+'trainImg' + '/' + img_name + '.png'
                if os.path.exists(objects[0]):
                    objects.insert(0, str(train_cnt))
                    train_cnt += 1
                    objects = ' '.join(objects) + '\n'
                    f.write(objects)
    f.close()


gen_train_txt()
gen_val_txt()
gen_test_txt()

