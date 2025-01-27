%Facts

exercise_frequency(riya, 3).
exercise_frequency(aditya, 1).
exercise_frequency(isha, 0).

junk_food_frequency(riya, low).
junk_food_frequency(aditya, moderate).
junk_food_frequency(isha, high).

sleep_time(isha, 8).
sleep_time(riya, 7).
sleep_time(aditya, 6).

screen_time(isha, low).
screen_time(riya, moderate).
screen_time(aditya, high).

% Rules

fit(Person) :-
    exercise_frequency(Person, Freq),
    Freq >= 2, % exercises atleast twice a week
    junk_food_frequency(Person, low), %junk food- low
    sleep_time(Person, Time),
    Time >= 7, % sleeps atleast for 7hrs
    (screen_time(Person, low); screen_time(Person, moderate)), %screen time low/moderate
    format('~w is fit.~n', [Person]).


unfit(Person) :-
    exercise_frequency(Person, Freq),
    Freq < 2, % exercises less than twice a week
    (junk_food_frequency(Person, moderate); junk_food_frequency(Person, high)), %junkfood-moderate/high
    sleep_time(Person, Time),
    Time < 7, % sleeps less than 7hrs
    screen_time(Person, high), %screen time high
    format('~w is unfit.~n', [Person]).
