#include "interMediate.h"
#include "codeOptimize.h"
#include "cast.h"
#include <fstream>

interMediate::interMediate() {

}

void interMediate::addCode(string str) {
	codeList.push_back(str);
}

void interMediate::printCode() {
	Optimize optimize(codeList);
	codeList = optimize.getCodeList();
	ofstream out("interMediate.txt",ios::app);
	out.clear();
	for (string s : codeList) {
		//cout << s << endl;
		out << s << "\n";
	}
}

string interMediate::createCodeforVar(string tempname, string op, varNode node1, varNode node2) {
	string result = tempname + " := ";
	if (node1.useAddress) {
		result += "*" + node1.name;
	}
	else {
		if (node1.num < 0) {
			result += node1.name;
		}
		else result += "var" + inttostr(node1.num);
	}
	
	result += " " + op + " ";

	if (node2.useAddress) {
		result += "*" + node2.name;
	}
	else {
		if (node2.num < 0) {
			result += node2.name;
		}
		else result += "var" + inttostr(node2.num);
	}

	return result;

}

string interMediate::createCodeforAssign(varNode node1, varNode node2) {
	string result;
	if (node1.useAddress) {
		result = "*" + node1.name + " := ";
	}
	else {
		result = "var" + inttostr(node1.num);
		result += " := ";
	}

	if (node2.useAddress) {
		result += "*" + node2.name;
	}
	else {
		if (node2.num < 0) {
			result += node2.name;
		}
		else result += "var" + inttostr(node2.num);
	}
	

	return result;
}

string interMediate::createCodeforParameter(varNode node) {
	string result = "PARAM ";
	result += "var" + inttostr(node.num);
	return result;
}

string interMediate::createCodeforReturn(varNode node) {
	string result = "RETURN ";
	if (node.useAddress) {
		result += "*" + node.name;
	}
	else {
		if (node.num < 0) {
			result += node.name;
		}
		else result += "var" + inttostr(node.num);
	}
	
	return result;
}

string interMediate::createCodeforArgument(varNode node) {
	string result = "ARG ";
	if (node.useAddress) {
		result += "*" + node.name;
	} 
	else {
		if (node.num < 0) {
			result += node.name;
		}
		else result += "var" + inttostr(node.num);
	}
	
	return result;
}

string interMediate::getNodeName(varNode node) {
	if (node.useAddress) {
		return "*" + node.name;
	}
	else {
		if (node.num < 0) {
			return node.name;
		}
		else return ("var" + inttostr(node.num));
	}

}

string interMediate::getarrayNodeName(arrayNode node) {
	return ("array" + inttostr(node.num));
}

string interMediate::getLabelName() {
	return "label" + inttostr(labelNum++);
}