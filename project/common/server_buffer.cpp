#include "server_buffer.h"

QByteArray IntToArray(qint32 source) {
  //Avoid use of cast, this is the Qt way to serialize objects
  QByteArray temp;
  QDataStream data(&temp, QIODevice::ReadWrite);
  data << source;
  return temp;
}

qint32 ArrayToInt(QByteArray source) {
  qint32 temp;
  QDataStream data(&source, QIODevice::ReadWrite);
  data >> temp;
  return temp;
}

QDataStream &operator <<(QDataStream &out, const ServerBuffer&dataStruct) {
  out.writeRawData((char*)&dataStruct,sizeof(dataStruct));
  return out;
}

QDataStream &operator >> (QDataStream &in, ServerBuffer& dataStruct) {
  dataStruct = ServerBuffer();
  in.readRawData((char*)&dataStruct, sizeof(dataStruct));
  return in;
}