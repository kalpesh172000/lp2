greeting([hi,hello]).
response(hi, ['hello!', 'hey there!', 'hi!', 'how are you?', 'what can I do for you?']).
response(hello, ['hello', 'hey there', 'hi', 'how are you', 'what can I do for you']).
response(_,['I am not sure what you mean...', 'Could you please rephrase that?', 'I am just a chatbot']).

respond(Query,Response):-
    (var(Query) ->
        Response = ['I am not sure what you mean...', 'Could you please rephrase that?', 'I am just a chatbot']
        ; response(Query,Response),!).
chat :-
  write("Charlie: Hello! How are you?"), nl,
  repeat,
  write('You: '),
  read_line_to_codes(user_input, Input),
  atom_codes(Query, Input),
  ( Query = bye -> write('Charlie: Goodbye!'), nl, ! ;
    (respond(Query,Response), random_member(reply,Response), write('charlie: '), write(reply),nl,fail
  )).
    