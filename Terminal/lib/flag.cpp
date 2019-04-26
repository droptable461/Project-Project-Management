#include "flag.h"

Flag::Flag(string argd){
	//should have some error checking
	string parameter = "";
    
    vector<string> str;
    string toSplit = argd;
    while(toSplit.size() > 0)
    {
        string toPush = toSplit.substr(0, toSplit.find(' '));
        if(toSplit[0] == '\"')
        {
            toSplit[0] = ' ';
            toPush = toSplit.substr(1,toSplit.find('\"')-1);
            toSplit = toSplit.substr(toSplit.find('\"')+1,toSplit.size());
        }
        else{
        if(toSplit.find(' ') < 0 || toSplit.find(' ') > toSplit.size())
            toSplit = "";
        toSplit  = toSplit.substr(toSplit.find(' ')+1, toSplit.size());
        }
        cout << toSplit << ":" << toPush << endl;
        str.push_back(toPush);
    }
   
	for(int i = str.size()-1; i >=0 ; --i){
		string arg = str[i];
		if(isNumber<int>(arg) || isNumber<double>(arg) || arg[0] != '-'){
			parameter = arg;	
		}else{
			arglist[arg.substr(1)] = {arg.substr(1),parameter,false,false};
			parameter = "";
		}
    }
}

string Flag::asString(){
	stringstream sout;
    for(auto p : arglist){
	    Argument a = p.second;
		sout << "\n" << p.first << "\t{" << a.parameter << "," << a.found << "," << a.asked << "}";
    }
	string rv = sout.str();
	if(rv.size() > 0)
		rv = rv.substr(1);
    return rv;
}

string Flag::errors(){
    stringstream sout;
    for(auto p : arglist){
        Argument a = p.second;
		if(!a.found && a.asked)
			sout << "\n" << a.name << "\t{" << a.parameter << "}";
    }
    string rv = sout.str();
    if(rv.size() > 0)
        rv = rv.substr(1);
    return rv;
}

bool Flag::wasFatal(){
	for(auto p : arglist){
		Argument a = p.second;
		if(a.asked && !a.found)
			return true;
	}
	return false;
}


bool Flag::getAsDouble(string arg,double& rv,string val){
	if(arglist.find(arg) != arglist.end()){
		string v = arglist[arg].parameter;
		if(v.size() == 0){
			v = val;
		}
		arglist[arg].found = isNumber<double>(v);
		if(arglist[arg].found){
			rv = stod(v);
		}
		arglist[arg].asked = true;
	}else{
		arglist[arg] = {arg,"",false,true};
	}
	return arglist[arg].found;
}

double Flag::getAsDouble(string arg, string val){
    double rv = 0;
    getAsDouble(arg,rv,val);
    return rv;
}


bool Flag::getAsInt(string arg,int& rv,string val){
    if(arglist.find(arg) != arglist.end()){
        string v = arglist[arg].parameter;
        if(v.size() == 0){
            v = val;
        }
        arglist[arg].found = isNumber<int>(v);
        if(arglist[arg].found){
            rv = stod(v);
        }
        arglist[arg].asked = true;
    }else{
        arglist[arg] = {arg,"",false,true};
    }
    return arglist[arg].found;
}

int Flag::getAsInt(string arg, string val){
	int rv = 0;
	getAsInt(arg,rv,val);
	return rv;
}


bool Flag::getAsString(string arg,string& rv,string val){
    if(arglist.find(arg) != arglist.end()){
        rv = arglist[arg].parameter;
        if(rv.size() == 0){
            rv = val;
        }
		arglist[arg].found = true;
        arglist[arg].asked = true;
    }else{
        arglist[arg] = {arg,"",false,true};
    }
    return arglist[arg].found;
}

string Flag::findFlag(string flag){
    if(arglist.find(flag) != arglist.end()){
        arglist[flag].found = true;
        arglist[flag].asked = true;
        return flag;
    }
    arglist[flag] = {flag,"",false,true};
    return "";
}


string Flag::findFlag(vector<string> flags){
    for(string f:flags){
        if(arglist.find(f) != arglist.end()){
            arglist[f].found = true;
            arglist[f].asked = true;
            return f;
        }
    }
    for(string f: flags){
        arglist[f] = {f,"",false,true};
    }


    return "";
}


string Flag::findFlag(vector<vector<string> > flagset){
	for(vector<string> flags: flagset){
		for(string f:flags){
			if(arglist.find(f) != arglist.end()){
				arglist[f].found = true;
				arglist[f].asked = true;
				for(string ff:flags){
					arglist[ff] = arglist[f];
				}
				return flags[0];
			}
		}
	}
    for(vector<string> flags: flagset){
		for(string f: flags){
			arglist[f] = {f,"",false,true};
		}
	}


	return "";
}



