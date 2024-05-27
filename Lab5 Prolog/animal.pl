% Animal identification rules
% To run, type      go.

go :- hypothesize(Animal), 
      write('I guess that the animal is: '), 
      write(Animal), nl, undo.

% Hypotheses to be tested
hypothesize(cheetah) :- cheetah, !.
hypothesize(tiger) :- tiger, !.
hypothesize(lion) :- lion, !.
hypothesize(giraffe) :- giraffe, !.
hypothesize(zebra) :- zebra, !.
hypothesize(ostrich) :- ostrich, !.
hypothesize(penguin) :- penguin, !.
hypothesize(albatross) :- albatross, !.
hypothesize(unknown). % no diagnosis

% Animal identification rules
cheetah :- mammal, carnivore,
           verify(has_tawny_color),
           verify(has_dark_spots).

tiger :- mammal, carnivore,
         verify(has_tawny_color),
         verify(has_black_stripes).

lion :- mammal, carnivore,
        verify(has_tawny_color),
        verify(has_hairy_tuft).

giraffe :- ungulate,
           verify(has_long_neck),
           verify(has_long_legs).

zebra :- ungulate,
         verify(has_black_stripes).

ostrich :- bird,
           verify(does_not_fly),
           verify(has_long_neck).

penguin :- bird,
           verify(does_not_fly),
           verify(swims),
           verify(is_black_and_white).

albatross :- bird,
             verify(appears_in_story_Ancient_Mariner),
             verify(flys_well).

% Classification rules
mammal :- verify(has_hair), !.
mammal :- verify(gives_milk).

bird :- verify(has_feathers), !.
bird :- verify(flys),
        verify(lays_eggs).

carnivore :- verify(eats_meat), !.
carnivore :- verify(has_pointed_teeth),
             verify(has_claws),
             verify(has_forward_eyes).

ungulate :- mammal, verify(has_hooves), !.
ungulate :- mammal, verify(chews_cud).

% How to ask questions
ask(Question) :-
    write('Does the animal have the following attribute: '),
    write(Question), write('? '),
    read(Response), nl,
    ( (Response == yes ; Response == y)
    -> assertz(yes(Question)) ;
    assertz(no(Question)), fail).

:- dynamic yes/1, no/1.

% How to verify something
verify(S) :- (yes(S) -> true ; (no(S) -> fail ; ask(S))).

% Undo all yes/no assertions
undo :- retract(yes(_)), fail.
undo :- retract(no(_)), fail.
undo.