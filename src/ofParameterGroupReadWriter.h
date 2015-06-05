//
//  ofParameterGroupReadWriter.h
//  natnetTracker
//
//  Created by Ovis aries on 2014/08/28.
//
//

#ifndef __natnetTracker__ofParameterGroupReadWriter__
#define __natnetTracker__ofParameterGroupReadWriter__

#include "ofMain.h"

class ofParameterGroupReadWriter{
public:
	ofParameterGroupReadWriter(){
		serializer = ofPtr<ofBaseFileSerializer> (new ofXml);
	}

	void setGroup(ofAbstractParameter *ptr);
	void save(string file);
	void load(string file);

	ofAbstractParameter *groupPtr;

	void setDefaultSerializer(ofPtr<ofBaseFileSerializer> serializer);
	void saveTo(ofBaseSerializer &serializer);
	void loadFrom(ofBaseSerializer &serializer);

	ofPtr<ofBaseFileSerializer> serializer;
};

#endif /* defined(__natnetTracker__ofParameterGroupReadWriter__) */
