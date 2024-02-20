#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        // tokenizer - splits the sent string on the sent seperator and sends it back as a vector
        // of strings. e.g 'hello how are you' -> ["hello", "how", "are", "you"]
        vector<string> tokenise(string input, char sep);
    
        // updates the sent map by adding the sent vector of words to it
        // with first order analyis. e.g.:
        // input: hello how are you ->
        // action: add the following entries to the map:
        // hello -> how
        // how -> are
        // are -> you
        // returns the updated map
        map<string,string> addWordsToMarkov(map<string,string> markov, string words);
    
        // returns a vector of strings representing the string keys of the sent map
        vector<string> getMapKeys(map<string,string> theMap);

        //function where we will use user input
        void onTextChange(string& text);
    
        //where you will implement your chatbot functionality
        void parrotBot(string inputText);
        
        //you need to create functions for the phraseBot, mangleBot & markovBot
        void phraseBot(string inputText);
        void mangleBot(string inputText);
        void markovBot(string inputText);

    

        //using an ofxGuiGroup so it stays stuck to the same spot
        ofxGuiGroup gui;
        // https://openframeworks.cc/documentation/types/ofParameter/
        ofParameterGroup parameters;
        ofParameter<string> textParameter;
    
        deque<string> messageBuffer;
        float lineHeight;

        vector<string> phrases;
        vector<string> words;

        map<string,string> wordChain;
};
