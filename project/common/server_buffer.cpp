#include "server_buffer.h"

QDataStream &operator <<(QDataStream &out, const ServerBuffer&dataStruct) {
  out.writeRawData((char*)&dataStruct,sizeof(dataStruct));
  return out;
}

QDataStream &operator >> (QDataStream &in, ServerBuffer& dataStruct) {
  dataStruct = ServerBuffer();
  in.readRawData((char*)&dataStruct, sizeof(dataStruct));
  return in;
}