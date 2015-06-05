//
//  ofxKsmrParamSync.h
//  SignageViewer
//
//  Created by Ovis aries on 2015/02/12.
//
//

#ifndef __SignageViewer__ofxKsmrParamSync__
#define __SignageViewer__ofxKsmrParamSync__

#include "ofMain.h"
#include "ofxKsmrOscDistributor.h"
#include "ofParameterGroupReadWriter.h"

class ofxKsmrParamSync{
public:

	ofxKsmrParamSync(){

	}
	~ofxKsmrParamSync(){
	}

	void sendRequest(string address,int port);
	void sendSerialized(string address,int port, bool withSave = false);
	void catchSerialized(string serialized, bool withSave = false);

	void setup(string syncId,ofxKsmrOscDistributor *dst,string externalPath = "");
	void setSyncId(string syncId){idAddress = syncId;}
	void update();
	bool getIsNewValue();

	bool load();
	void save();

	ofParameterGroup* getGroup(){return &params;}

protected:

	string	extPath;
	string	idAddress;
	int		currentPort;
	ofPtr<ofxKsmrOscTip> receiver;

	ofParameterGroup params;
	ofParameterGroupReadWriter paramRW;
	bool isNewValue;
};

#endif /* defined(__SignageViewer__ofxKsmrParamSync__) */
