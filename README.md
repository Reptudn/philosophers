# Philosophers
Eat, Sleep, Spaghetti, repeat. This project is about learning how threads work by precisely timing a group of philosophers on when to pick up forks and eat spaghetti without dying from hunger. 

## ✅ Final Grade 100/125

## Useful
[Tutorial Series about C threads](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)

[Medium Tutorial and philo explanation](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2)

[Philosopher Visualizer](https://nafuka11.github.io/philosophers-visualizer/)

## Don't forget to test with valgrind
`valgrind --tool=helgrind`

## Input
- number_of_philosophers: The number of philosophers and also the number of forks.
- time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
- time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
- number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

## Tests
### Mandatory
#### Eval-Sheet
- [x] Test: 1 800 200 200. The philosopher should not eat and should die.
- [x] Test: 5 800 200 200. No philosopher should die.
- [x] Test: 5 800 200 200 7. No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
- [x] Test: 4 410 200 200. No philosopher should die.
- [x] Test: 4 310 200 100. One philosopher should die.

#### other
- [x] 5 600 150 150. no one should die
- [x] 100 800 200 200. no one should die
- [x] 105 800 200 200. no one should die
- [x] 200 800 200 200. no one should die
- [x] 4 200 205 200. a philo should die
- [x] 4 410 200 200 10. no one should die, simulation should stop after 10 eats
- [x] Invalid Input tests with negative numbers and with invalid argv

### Bonus
- Test: 5 800 200 200. No philosopher should die.
- Test: 5 800 200 200 7. No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
- Test: 4 410 200 200. No philosopher should die.
- Test: 4 310 200 100. One philosopher should die.
