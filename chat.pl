% Knowledge base
knowledge(hello, 'Hello! How can I assist you today?'). % Storing a knowledge entry for the input 'hello'
knowledge(goodbye, 'Goodbye! Have a great day!'). % Storing a knowledge entry for the input 'goodbye'
knowledge(thank_you, 'Youre welcome!'). % Storing a knowledge entry for the input 'thank_you'
knowledge(who_is(john), 'John is a software engineer.'). % Storing a knowledge entry for the input 'who_is(john)'
knowledge(who_is(mary), 'Mary is a doctor.'). % Storing a knowledge entry for the input 'who_is(mary)'
knowledge(who_is(sarah), 'Sarah is a teacher.'). % Storing a knowledge entry for the input 'who_is(sarah)'

% Rules
response(Input, Output) :- knowledge(Input, Output), !. 
response(_, 'I'm sorry, I don't have an answer for that.').

% Main loop
chat :- % Main chat loop
    write('Chatbot: '), % Displaying a prompt for user input
    read(Input), % Reading user input
    response(Input, Output), % Generating a response based on the input
    write('Response: '), % Displaying a prompt for the generated response
    write(Output), % Displaying the generated response
    nl, % New line
    chat. % Recursive call to continue the chat loop

    nl, % New line
    random_response(Output), % Generating a random response based on the stored knowledge entries
    write('Response: '), % Displaying a prompt for the random response
    write(Output), % Displaying the random response
    nl, % New line
    chat. % Recursive call to continue the chat loop

random_response(Output) :- % Defining a rule for generating a random response
    findall(Response, knowledge(Input, Response), Responses), % Collecting all possible responses from the knowledge base
    random_member(Output, Responses). % Selecting a random response from the collected responses