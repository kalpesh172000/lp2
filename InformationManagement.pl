% Facts
employee(john, developer).
employee(sara, manager).
employee(mark, designer).
employee(peter, developer).
employee(lisa, designer).

skill(john, java).
skill(john, python).
skill(sara, management).
skill(mark, photoshop).
skill(peter, java).
skill(peter, python).
skill(lisa, photoshop).
skill(lisa, illustrator).

% Rules
has_skill(Employee, Skill) :-
    employee(Employee, _),
    skill(Employee, Skill).

has_role(Employee, Role) :-
    employee(Employee, Role).

% Queries
% Check if John has the skill 'java'.
% ?- has_skill(john, java).

% Check if Sara is a manager.
% ?- has_role(sara, manager).
