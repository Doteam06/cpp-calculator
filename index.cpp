#include <bits/stdc++.h>

double addition(double num1,double num2){
    return num1+num2;
}

double subtraction(double num1,double num2){
    return num1-num2;
}

double divition(double num1,double num2){
    return num1/num2;
}

double multiplication(double num1,double num2){
    return num1*num2;
}

double rooting(double num1,double num2){
    return pow(num1, 1.0 / double(num2));
}

double exponentiation(double num1,double num2){
    return pow(num1,num2);
}

double stringToInt(std::string num){
    int counter=0, sizeNum=num.size();
    double finalNum=0;
    for(char i : num ){
        if (i==int('.')){sizeNum=counter; break;}
        counter++;
    }
    counter=0;
    for(char i : num){
        if (i==int('.')) continue;
        counter++;
        finalNum += pow(10,sizeNum-counter)*(i-48);
    }
    return finalNum;
}

double selectOperation(std::string number1, std::string number2,int lastOperation){
    double primary=0, secundary=0, result=0;
    primary=stringToInt(number1); secundary=stringToInt(number2); 
    switch (lastOperation)
    {
        case 42: result+=multiplication(primary,secundary); break;
        case 43: result+=addition(primary,secundary); break;
        case 45: result=subtraction(primary,secundary); break;
        case 47: result+=divition(primary,secundary); break;
        case 94: result+=exponentiation(primary,secundary); break;
        case 93: result+=rooting(primary,secundary); break;
    }
    return result;
}


double calcOperation(std::string operation){
    int lastOperation=0, OperationCuantity=0, totalOperationCuantity=0 , OperationCuantity2, OpenParentesis=0, index=0;
    std::vector<int> lastOpenParentesisIndex; 
    double result=0;
    std::string number1="", number2="";
    bool complexOperation=false, firstNumber=true, calc=false; 

    for (char value : operation){
        if (int(value)==42 || int(value)==43 || int(value)==45 || int(value)==47 || int(value)==94 || int(value)==40 || int(value)==41 || int(value)==91 || int(value)==93 || int(value)==int(' ') ) {
            if (int(value)==40){
                OpenParentesis++;
                lastOpenParentesisIndex.push_back(index);
            }
            else if (int(value)==41 && OpenParentesis){
                //
                firstNumber=true; calc=false; OperationCuantity2=0;
                for(int i=lastOpenParentesisIndex.back()+1;i<index+1;i++){
                    if (int(operation[i])==42 || int(operation[i])==43 || int(operation[i])==45 || int(operation[i])==47 || int(operation[i])==94 || int(operation[i])==41){
                        if (firstNumber==false) {
                            result+=selectOperation(number1,number2,lastOperation);
                            if (int(operation[i])==45) {number1=""; number2=std::to_string(result);}
                            else {number1="",number2="";}
                            firstNumber=true; 
                            OperationCuantity2++;totalOperationCuantity++;
                        } 
                        else {
                            if (OperationCuantity2==0){
                                calc=true;
                            }
                            else {
                                result+=selectOperation(number1,number2,lastOperation);
                                if (int(operation[i])==45) {number1=std::to_string(result); number2="";}
                                else {number1=""; number2="";}
                                OperationCuantity2++;totalOperationCuantity++;
                            }
                            firstNumber=false;
                        }
                        lastOperation=int(operation[i]);
                    }
                    else {
                        if (firstNumber==true) number1+=char(operation[i]);
                        else number2=number2+char(operation[i]);
                    }
                }

                //
                std::string string1 = operation.substr(0, lastOpenParentesisIndex.back());
                std::string string2 = operation.substr(index+1);
                operation = string1 + std::to_string(result) + string2;
                OpenParentesis--;
                std::cout<<"("<<totalOperationCuantity<<") "<<operation<<"\n";
                lastOpenParentesisIndex.erase(lastOpenParentesisIndex.begin() + lastOpenParentesisIndex.size()-1);
            }
            else if(!OpenParentesis){
                if (firstNumber==false) {
                    result+=selectOperation(number1,number2,lastOperation);
                    if (int(value)==45) {number1=""; number2=std::to_string(result);}
                    else {number1="",number2="";}
                    firstNumber=true; 
                    OperationCuantity++;totalOperationCuantity++;
                } 
                else {
                    if (OperationCuantity==0){
                        calc=true;
                    }
                    else {
                        result+=selectOperation(number1,number2,lastOperation);
                        if (int(value)==45) {number1=std::to_string(result); number2="";}
                        else {number1=""; number2="";}
                        OperationCuantity++;totalOperationCuantity++;
                    }
                    firstNumber=false;
                }
            }
            lastOperation=int(value);
        }
        else if(!OpenParentesis){
            if (firstNumber==true) number1+=char(value);
            else number2=number2+char(value);
        }
        index++;  
    }
    std::cout<<"\n\nFinal Result: ";
    return result;     
}

    
int main(){
    std::string operation;

    std::cout << "Welcome to the Terminal Calculator." << std::endl << std::endl;
    std::cout << "Available operations and their symbols:" << std::endl;
    std::cout << "- Multiplication: {*} " << std::endl;
    std::cout << "- Addition: {+} " << std::endl;
    std::cout << "- Subtraction: {-} " << std::endl;
    std::cout << "- Square Root: {n[number]} " << std::endl;
    std::cout << "- Exponentiation: {^} " << std::endl;

    std::cout << "\nPlease enter your operation: \n> ";
    std::cin >> operation;

    std::cout << "\nSteps: \n" << calcOperation(operation + " ") <<"\n"<< std::endl;

}