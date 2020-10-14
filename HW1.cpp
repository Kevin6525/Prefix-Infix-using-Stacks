#include <iostream> //Read input
#include <stack> //STL Stack class
#include <algorithm> //remove for modifying the input
using namespace std;

//Function declarations
bool isOperator(string);
bool isPrefix(string);
string prefixToInfix(string);
string infixToPrefix(string);
string modifyInput(string);
int operatorPriority(char);

//Check to see if the character we are pointing at is an operator or not
//Returns true/false
bool isOperator(char inputValue)
{
	if(inputValue == '+' || inputValue == '-' || inputValue == '*' || inputValue == '/')
	{
		return true;
	}
	else
	{
		return false;
	}
}
//Checks if the input is in Prefix form
//Returns true/false
bool isPrefix(string inputExpression)
{
	if(isOperator(inputExpression[0]))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//Converts Prefix input to Infix expression
string prefixToInfix(string inputExpression)
{
	//Create a stack to store the operands or numbers in the expression
	stack<string> numberStack;
	//We read the input from right to left since it is in Prefix form
	for(int i = inputExpression.length()-1; i >=0; i --)
	{
		//Read until we find an operator
		if(isOperator(inputExpression[i]))
		{
			//Once we find an operator, we must process the expression
			//We access the top two operands from numberStack and pop them to traverse through the stack
			//We then create a new expression by combining the two operands with the operator
			//We save the expression by pushing it back onto the numberStack
			//Note: We don't need to use an operatorStack for this function since we update the expression everytime we encounter an operator
			string operand1 = numberStack.top();
			numberStack.pop();
			string operand2 = numberStack.top();
			numberStack.pop();
			string newExpression = "(" + operand1 + inputExpression[i] + operand2 + ")"; 
			numberStack.push(newExpression);
		}
		//If we read anything other than an operator
		else
		{
			//We add the operand to numberStack and cast it as a string 
			numberStack.push(string(1, inputExpression[i]));
		}
	}
	//Return the top of numberStack which should have the completed expression in Infix form
	return numberStack.top();
}
//Converts from Infix form to Prefix form
string infixToPrefix(string inputExpression)
{
	//numberStack is for the operands/numbers in the expression
	//operatorStack is for the operators in the expression
	stack<string> numberStack;
	stack<char> operatorStack;
	//Loop through the input expression
	for(int i = 0; i < inputExpression.length(); i ++)
	{
		//If we encounter an open parenthesis, we push it onto the operatorStack
		if(inputExpression[i] == '(')
		{
			operatorStack.push(inputExpression[i]);
		}
		//Check if we encounter a closed parenthesis
		else if (inputExpression[i] == ')')
		{
			//We check that the operator stack is not empty and push through the stack until we find the opening paranthesis
			while(!operatorStack.empty() && operatorStack.top() != '(')
			{
				//Create the prefix expression and pop two items off numberStack and one off operatorStack
				//Push the new prefix expression onto numberStack
				//We keep looping until we either have no more operators in operatorStack or we encounter an open parenthesis in numberStack
				string operand1 = numberStack.top();
				numberStack.pop();
				string operand2 = numberStack.top();
				numberStack.pop();
				char operator1 = operatorStack.top();
				operatorStack.pop();
				string expression = operator1 + operand2 + operand1;
				numberStack.push(expression);
			}
			//Once we encounter an opening paranthesis, we pop it off from the stack
			//This ensures we have a closed parenthesis for every open one
			operatorStack.pop();
		}
		//If the char is an operator, we need to check to see if it has less "priority" than 
		//what is already the top of the operatorStack. If the char we are pointing at has less
		//priority, then we create the expression with the higher priority operator and the operands
		//and push the expression onto the numberStack
		else if(isOperator(inputExpression[i]))
		{
			
			while(!operatorStack.empty() && operatorPriority(inputExpression[i]) <= operatorPriority(operatorStack.top()))
			{
				//If the operator we point to has less priority than what we have in the top of operatorStack
				//We must create the Prefix expression with the higher priority operator
				//We push the expression onto numberStack doing the same thing as above
				//Note: we use <= because if they are of equal priority, then the one we read first has higher
				//priority than the one we are currently pointing to
				string operand1 = numberStack.top();
				numberStack.pop();
				string operand2 = numberStack.top();
				numberStack.pop();
				char operator1 = operatorStack.top();
				operatorStack.pop();
				string expression = operator1 + operand2 + operand1;
				numberStack.push(expression);
			}
			//Push the higher priority operator onto operatorStack
			operatorStack.push(inputExpression[i]);
		}
		//This handles when we point to an operand
		//We will cast the operand to a string and push it onto numberStack
		else 
		{
			numberStack.push(string(1, inputExpression[i]));
		}
	}
	//We go through the operatorStack until it is empty and update the expression
	//We continue to update numberStack and push the new expression to the top
	while (!operatorStack.empty())
	{
		string operand1 = numberStack.top();
		numberStack.pop();
		string operand2 = numberStack.top();
		numberStack.pop();
		char operator1 = operatorStack.top();
		operatorStack.pop();
		string expression = operator1 + operand2 + operand1;
		numberStack.push(expression);
	}
	//The final Prefix expression should be in the top of numberStack
	return numberStack.top();
}
//This function modifies the input to ensure there are no whitespaces between characters
string modifyInput(string inputExpression)
{
	//Note: remove does not actually remove anything so we use erase to do so. Remove just finds where the whitespace is
	inputExpression.erase(remove(inputExpression.begin(), inputExpression.end(), ' '), inputExpression.end());
	return inputExpression;
}
//This function gives a quantitative definition to "prioritize" operators
int operatorPriority(char operator1)
{
	if(operator1 == '-' || operator1 == '+')
	{
		return 1;
	}
	else if (operator1 == '*' || operator1 == '/')
	{
		return 2;
	}
	else
	{
		return 0;
	}
}
int main()
{
	string inputExpression;
	cout<<"Please enter a prefix or infix expression (or 'q' to quit): ";
	getline(cin, inputExpression);
	while(inputExpression.compare("Q")!= 0 && inputExpression.compare("q")!= 0)
	{
		inputExpression = modifyInput(inputExpression);
		if(isPrefix(inputExpression))
		{
			cout<<"You entered a prefix expression. It will be converted to an infix expression"<<endl;
			cout<<"Infix Expression: "<<prefixToInfix(inputExpression)<<endl;
		}	
		else
		{
			cout<<"You entered a infix expression. It will be converted to an prefix expression"<<endl;
			cout<<"Prefix Expression: "<<infixToPrefix(inputExpression)<<endl;
		}
		cout<<"Please enter a prefix or infix expression (or 'q' to quit): ";
		getline(cin, inputExpression);
	}
	cout<<"Thank you for using the program";
	return 0;	
}
