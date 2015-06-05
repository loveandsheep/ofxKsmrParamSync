//
//  ofParameterGroupReadWriter.cpp
//  natnetTracker
//
//  Created by Ovis aries on 2014/08/28.
//
//

#include "ofParameterGroupReadWriter.h"

void ofParameterGroupReadWriter::setGroup(ofAbstractParameter *ptr){
	groupPtr = ptr;
}

void ofParameterGroupReadWriter::save(string file){
	serializer->load(file);
	saveTo(*serializer);
	serializer->save(file);
}

void ofParameterGroupReadWriter::load(string file){
	serializer->load(file);
	loadFrom(*serializer);
}

void ofParameterGroupReadWriter::setDefaultSerializer(ofPtr<ofBaseFileSerializer> _serializer){
	serializer = _serializer;
}

void ofParameterGroupReadWriter::saveTo(ofBaseSerializer &serializer){
	serializer.serialize(*groupPtr);
}

void ofParameterGroupReadWriter::loadFrom(ofBaseSerializer &serializer){
	serializer.deserialize(*groupPtr);
}