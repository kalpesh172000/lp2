
response(hello, ['hi there!', 'hello!', 'hey!', 'nice to see you!', 'how are you?']).
response(hi, ['hello!', 'hey there!', 'hi!', 'how are you?', 'what can I do for you?']).
response(hey, ['hello!', 'hi!', 'hey there!', 'what can I do for you?', 'nice to see you!']).
response(greetings, ['howdy!', 'hello!', 'hi!', 'what can I do for you?', 'nice to see you!']).
response('howdy!', ['hello!', 'hi!', 'hey!', 'nice to see you!', 'what can I do for you?']).

response(_, ['I am not sure what you mean...', 'Could you please rephrase that?', 'I am just a simple chatbot...', 'I am not equipped to answer that.']).


respond(Query, Response) :-
    (var(Query) -> 
        Response = ['I am not sure what you mean...', 'Could you please rephrase that?', 'I am just a simple chatbot...', 'I am not equipped to answer that.']
    ; response(Query, Response),!
    ).

chat :-
    write('Chatbot: Hello! How can I help you?'), nl,
    repeat,
    write('You: '),
    read_line_to_codes(user_input, Input),
    atom_codes(Query, Input),
    (Query = bye -> write('Chatbot: Goodbye!'); 
    (respond(Query, Response), random_member(Reply, Response), write('Chatbot: '), write(Reply), nl, fail)),
    Query = bye, !.

/* 

C:\Users\ASHISH\Desktop\TE_A_05_LP2>C:/progra~1/swipl/bin/swipl
Welcome to SWI-Prolog (threaded, 64 bits, version 9.2.3)
SWI-Prolog comes with ABSOLUTELY NO WARRANTY. This is free software.
Please run ?- license. for legal details.

For online help and background, visit https://www.swi-prolog.org
For built-in help, use ?- help(Topic). or ?- apropos(Word).

1 ?- [chatbot].
true.

2 ?- chat.
Chatbot: Hello! How can I help you?
You: hi
Chatbot: hey there!
You: how is weather like?
Chatbot: I am just a simple chatbot...
You: what is the weather like?
Chatbot: The weather is pleasant.
You: what time is it?
15:57:52Chatbot: Time flies when you're having fun!
You: bye
Chatbot: Goodbye!
true.

3 ?-

*/