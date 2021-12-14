#include "model.h"

Model::Model()
{

}

void Model::setPreviewImage(QPixmap pixmap){
    this->previewImage = pixmap;
};

void Model::setAsmImage(QPixmap pixmap){
    this->asmImage = pixmap;
};

void Model::setCImage(QPixmap pixmap){
    this->cImage = pixmap;
};

void Model::setImagePath(QString path){
    this->imagePath = path;
};

void Model::setMethodIndex(int number){
    this->methodIndex = number;
};

void Model::setPreviewWidth(int number){
    this->previewWidth = number;
};

void Model::setPreviewHeight(int number){
    this->previewHeight = number;
};

void Model::setResultWidth(int number){
    this->resultWidth = number;
};

void Model::setResultHeight(int number){
    this->resultHeight = number;
};

int Model::getPreviewWidth(){
    return this->previewWidth;
};

int Model::getPreviewHeight(){
    return this->previewHeight;
};

int Model::getResultWidth(){
    return this->resultWidth;
};

int Model::getResultHeight(){
    return this->resultHeight;
};

int Model::getMethodIndex(){
    return this->methodIndex;
}

QPixmap Model::getPreviewImage(){
    return this->previewImage;
};

QPixmap Model::getAsmImage(){
    return this->asmImage;
};

QPixmap Model::getCImage(){
    return this->cImage;
};

QString Model::getImagePath(){
    return this->imagePath;
}
