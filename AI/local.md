I've received your **30-page PDF: `1. Local Search-II.pdf`**.

I've checked the document, including its slides, diagrams, mathematical expressions, pseudocode, and handwritten annotations. The PDF is readable, including the portions that are available only as images.

The lecture is titled **Metaheuristic Search and Other Search Techniques**.

It covers five major areas:

| Section | Topics | PDF Pages |
|---|---|---|
| 1 | Simulated Annealing | 2–4 |
| 2 | Evolutionary Algorithms and Genetic Algorithm | 5–17 |
| 3 | Non-deterministic Actions and AND-OR Search | 18–22 |
| 4 | Partially Observable Environments and Belief States | 23–26 |
| 5 | Online Search and Unknown Environments | 27–30 |

I'll preserve the order and terminology of your professor's slides while adding the background knowledge, mathematical explanations, examples, and additional details needed to understand the concepts at M.Tech level.

I'll also explain the diagrams and pseudocode rather than simply copying them into notes.

# AI – Detailed Exam Preparation Notes
## Lecture: Metaheuristic Search and Other Search Techniques

# PART 1: SIMULATED ANNEALING

*(PDF pages 2–4)*

## 1. Introduction: What is Simulated Annealing?

Before understanding Simulated Annealing, we need to understand two things:

1. Optimization problems.
2. Local Search algorithms.

### 1.1 What is an Optimization Problem?

An optimization problem is a problem in which we want to find the best possible solution among many possible solutions.

The best solution could mean:
- Maximum profit.
- Minimum cost.
- Minimum distance.
- Maximum accuracy.
- Minimum execution time.

For example:

Suppose you want to travel from IIT Ropar to Delhi.

You have several possible routes:

| Route | Distance |
|---|---:|
| Route A | 250 km |
| Route B | 270 km |
| Route C | 240 km |
| Route D | 260 km |

Your objective is to find the route with minimum distance.

Here:
- Possible routes = Search space.
- Distance = Objective function.
- Route C = Optimal solution.

Mathematically, an optimization problem can be represented as:

\[
\min_{x\in S} f(x)
\]

Where:

- \(S\) = Set of all possible solutions.
- \(x\) = A particular solution.
- \(f(x)\) = Objective function.
- \(\min\) = Find the minimum value.

For a maximization problem:

\[
\max_{x\in S} f(x)
\]

**Important:** An optimization problem can have an enormous number of possible solutions. Checking every solution may be computationally expensive.

This is where local search and metaheuristic algorithms become useful.

## 2. Understanding Local Search

Local Search is an optimization technique in which we start with one solution and repeatedly move towards a better neighboring solution.

Instead of exploring the entire search tree, we concentrate on the current solution and its neighboring solutions.

### Example

Suppose we want to maximize:

\[
f(x)=-(x-5)^2+25
\]

Assume that \(x\) can take integer values from 0 to 10.

Some values are:

| x | f(x) |
|---:|---:|
| 0 | 0 |
| 1 | 9 |
| 2 | 16 |
| 3 | 21 |
| 4 | 24 |
| 5 | 25 |
| 6 | 24 |
| 7 | 21 |
| 8 | 16 |
| 9 | 9 |
| 10 | 0 |

The maximum value is:

\[
f(5)=25
\]

A local search algorithm might start at \(x=1\).

It examines neighboring values:

\[
x=0,\quad x=2
\]

Since:

\[
f(2)>f(1)
\]

It moves to \(x=2\).

Then it moves to \(x=3\), followed by \(x=4\), and finally \(x=5\).

It has reached the maximum.

But there is a problem with ordinary local search.

### 2.1 What is a Local Maximum?

A local maximum is a solution that is better than all its immediate neighboring solutions but is not necessarily the best solution in the entire search space.

Consider this conceptual landscape:

- A hill represents a high objective-function value.
- A valley represents a low objective-function value.
- The highest hill represents the global maximum.
- A smaller hill represents a local maximum.

An ordinary hill-climbing algorithm can get stuck on a smaller hill because all its immediate neighboring solutions are worse.

It cannot reach the higher hill without temporarily moving downhill.

This problem is called getting stuck in a local optimum.

### 2.2 Local Maximum vs Global Maximum

| Local Maximum | Global Maximum |
|---|---|
| Better than neighboring solutions | Best among all possible solutions |
| May not be the best overall solution | Best overall solution |
| Can trap local search algorithms | Desired solution in maximization |
| Multiple local maxima may exist | Global maximum may be unique or non-unique |

**Example:**

Suppose the objective-function values of different solutions are:

\[
10,\ 15,\ 12,\ 30,\ 18,\ 20
\]

If the search gets stuck at 20 because its neighbors are worse, it has found a local maximum.

However, the global maximum is:

\[
30
\]

We need a technique that allows the algorithm to escape local optima.

This brings us to Simulated Annealing.

---

## 3. What is Simulated Annealing?

Simulated Annealing (SA) is a probabilistic optimization algorithm inspired by the physical process of annealing in metallurgy.

According to your professor's slide on page 2, annealing is a heat-treatment process used mainly to increase the ductility and reduce the hardness of a material.

### 3.1 Understanding Physical Annealing

Imagine a piece of metal.

The physical annealing process involves:

1. Heating the metal to a high temperature.
2. Allowing the material's internal structure to change.
3. Gradually cooling it.
4. Allowing it to settle into a more stable structure.

The gradual cooling process is important.

If the metal cools too quickly, it may not reach the desired stable structure.

### 3.2 How is This Related to Artificial Intelligence?

Simulated Annealing applies a similar idea to optimization.

Instead of heating and cooling metal, we control the probability of accepting worse solutions.

The basic idea is:

**At high temperature:**
- The algorithm explores more freely.
- It can accept worse solutions.
- It can escape local optima.

**At low temperature:**
- The algorithm becomes more selective.
- It rarely accepts worse solutions.
- It concentrates on improving the current solution.

Eventually, the temperature approaches zero, and the algorithm stops accepting worse solutions.

This is the central idea of Simulated Annealing.

### 3.3 Definition

Simulated Annealing is a stochastic local search algorithm that sometimes accepts worse neighboring solutions with a certain probability to escape local optima. This probability gradually decreases as the temperature decreases.

Your professor describes it on page 3 as:

- A variant of stochastic hill climbing.
- A method that allows random downhill moves.
- A technique in which the frequency of downhill moves gradually decreases.

### 3.4 Why Does Simulated Annealing Accept Worse Solutions?

Consider this situation:

You are standing on a small hill, but a much higher hill exists nearby.

To reach the higher hill, you must first descend into a valley.

Ordinary hill climbing refuses to descend because doing so decreases the objective-function value.

Simulated Annealing sometimes allows this downhill movement.

This gives the algorithm an opportunity to explore a different region of the search space.

That is why Simulated Annealing is less likely to get permanently stuck in a local optimum.

## 4. Mathematical Foundation of Simulated Annealing

This is one of the most important parts of the lecture from an examination perspective.

### 4.1 Temperature (T)

Temperature is a control parameter that determines how willing the algorithm is to accept worse solutions.

It is not the actual physical temperature. It is a mathematical parameter.

For example:

| Temperature | Behaviour |
|---|---|
| Very high | More exploration; worse solutions are frequently accepted |
| Moderate | Some worse solutions are accepted |
| Low | Worse solutions are rarely accepted |
| Zero | Worse solutions are never accepted |

### 4.2 Acceptance Probability

Your professor's slide on page 3 introduces the probability:

\[
P=e^{\Delta E/T}
\]

The pseudocode on page 4 defines:

\[
\Delta E=VALUE(current)-VALUE(next)
\]

This convention corresponds to a minimization problem, where lower values are better.

Therefore:

**Case 1: Next solution is better**

Suppose:

\[
VALUE(current)=50
\]

\[
VALUE(next)=30
\]

Then:

\[
\Delta E=50-30=20
\]

Since:

\[
\Delta E>0
\]

We accept the next solution directly.

No probability calculation is required.

**Case 2: Next solution is worse**

Suppose:

\[
VALUE(current)=30
\]

\[
VALUE(next)=50
\]

Then:

\[
\Delta E=30-50=-20
\]

Now:

\[
P=e^{-20/T}
\]

The algorithm accepts this worse solution only with probability \(P\).

This is the most important mathematical concept in Simulated Annealing.

### 4.3 Solved Numerical Example

Suppose:

- Current solution cost = 100.
- Next solution cost = 110.
- Temperature = 10.

We want to determine the probability of accepting the next solution.

**Step 1: Calculate the difference.**

\[
\Delta E=100-110=-10
\]

**Step 2: Apply the probability formula.**

\[
P=e^{\Delta E/T}
\]

\[
P=e^{-10/10}
\]

\[
P=e^{-1}
\]

\[
\boxed{P\approx0.3679}
\]

Therefore, the probability of accepting the worse solution is approximately:

\[
\boxed{36.79\%}
\]

Now suppose the temperature increases to 100.

\[
P=e^{-10/100}
\]

\[
P=e^{-0.1}
\]

\[
\boxed{P\approx0.9048}
\]

The probability is now approximately 90.48%.

**Observation:** At higher temperatures, the algorithm is more willing to accept worse solutions.

### 4.4 Why Does Temperature Matter?

Let's compare three temperatures for the same deterioration in solution quality:

\[
\Delta E=-10
\]

| Temperature | Acceptance Probability |
|---:|---:|
| 1 | 0.0000454 |
| 10 | 0.3679 |
| 100 | 0.9048 |

Notice that:

- At temperature 1, accepting a worse solution is extremely unlikely.
- At temperature 10, it is reasonably possible.
- At temperature 100, it is highly likely.

This explains why the algorithm starts with a high temperature and gradually cools down.

### 4.5 Temperature Schedule

A temperature schedule determines how temperature changes over time.

Your professor refers to this as:

\[
T=schedule(t)
\]

Where:
- \(T\) = Current temperature.
- \(t\) = Current iteration.
- \(schedule(t)\) = Function that determines the temperature at iteration \(t\).

One commonly used cooling schedule is exponential cooling:

\[
\boxed{T_t=T_0\alpha^t}
\]

Where:

- \(T_0\) = Initial temperature.
- \(\alpha\) = Cooling factor, generally between 0 and 1.
- \(t\) = Iteration number.

Example:

Suppose:

\[
T_0=100
\]

\[
\alpha=0.9
\]

Then:

| Iteration | Temperature |
|---:|---:|
| 0 | 100 |
| 1 | 90 |
| 2 | 81 |
| 3 | 72.9 |
| 4 | 65.61 |
| 5 | 59.049 |

The temperature gradually decreases.

**Important examination point:** If the cooling schedule is too fast, the algorithm may become trapped in a local optimum. If cooling is sufficiently slow, it gets more opportunities to explore the search space.

---

## 5. Simulated Annealing Algorithm

Your professor provides the algorithm's pseudocode on page 4.

Let's understand every instruction.

### 5.1 Pseudocode

```text
function SIMULATED-ANNEALING(problem, schedule)
    current = problem.INITIAL

    for t = 1 to infinity:
        T = schedule(t)

        if T = 0:
            return current

        next = randomly selected successor of current

        ΔE = VALUE(current) - VALUE(next)

        if ΔE > 0:
            current = next

        else:
            current = next only with probability e^(ΔE/T)
```

### 5.2 Explanation of Every Step

**Step 1: Initialize the current solution**

```text
current = problem.INITIAL
```

Select an initial solution randomly or according to the problem definition.

**Step 2: Calculate temperature**

```text
T = schedule(t)
```

Determine the temperature for the current iteration.

**Step 3: Check the stopping condition**

```text
if T = 0:
    return current
```

If the temperature reaches zero, terminate the algorithm.

In practical implementations, we often use a small threshold or a maximum iteration count instead.

**Step 4: Select a neighboring solution**

```text
next = randomly selected successor of current
```

Choose a neighboring solution randomly.

**Step 5: Calculate the difference**

```text
ΔE = VALUE(current) - VALUE(next)
```

For minimization:

- Positive difference means improvement.
- Negative difference means deterioration.
- Zero means equal cost.

**Step 6: Accept or reject**

If the next solution is better, accept it.

Otherwise, calculate the acceptance probability:

\[
P=e^{\Delta E/T}
\]

Generate a random number:

\[
r\sim Uniform(0,1)
\]

Accept the worse solution if:

\[
r<P
\]

Otherwise, retain the current solution.

### 5.3 Complete Numerical Iteration Example

Suppose the current cost is 50.

A randomly selected neighboring solution has cost 55.

Temperature:

\[
T=10
\]

We calculate:

\[
\Delta E=50-55=-5
\]

Acceptance probability:

\[
P=e^{-5/10}
\]

\[
P=e^{-0.5}=0.6065
\]

Generate a random number:

\[
r=0.4
\]

Since:

\[
0.4<0.6065
\]

We accept the worse solution.

The new current cost becomes:

\[
55
\]

Now suppose the randomly generated number is:

\[
r=0.8
\]

Since:

\[
0.8>0.6065
\]

We reject the worse solution and retain cost 50.

### 5.4 Important Properties of Simulated Annealing

1. It is a probabilistic search algorithm.
2. It is a variant of stochastic hill climbing.
3. It can accept worse solutions.
4. It uses a temperature parameter.
5. Its acceptance probability decreases as temperature decreases.
6. It helps escape local optima.
7. Its performance depends heavily on the cooling schedule.

### 5.5 Applications

Simulated Annealing is useful in:

- Travelling Salesperson Problem (TSP).
- Scheduling problems.
- Circuit design.
- Resource allocation.
- Engineering optimization.
- Parameter optimization in machine learning.

**Example: Travelling Salesperson Problem**

Suppose a salesperson has to visit five cities and return to the starting city.

There are multiple possible visiting orders.

The objective is to minimize the total travelling distance.

Simulated Annealing can:
1. Start with a random visiting order.
2. Swap two cities to generate a neighboring route.
3. Accept shorter routes.
4. Sometimes accept longer routes.
5. Gradually reduce the probability of accepting longer routes.

This helps it escape locally optimal routes.

---

## 6. Advantages and Disadvantages of Simulated Annealing

| Advantages | Disadvantages |
|---|---|
| Can escape local optima | Does not guarantee a global optimum in practical finite runs |
| Simple implementation | Cooling schedule requires careful selection |
| Can handle large search spaces | May require many iterations |
| Does not require gradient information | Performance depends on parameter selection |
| Works with discrete and continuous problems | May converge slowly |

### 6.1 Important Comparison: Hill Climbing vs Simulated Annealing

| Feature | Hill Climbing | Simulated Annealing |
|---|---|---|
| Search type | Local search | Stochastic local search |
| Accepts better solutions | Yes | Yes |
| Accepts worse solutions | Generally no | Sometimes |
| Randomness | Depends on variant | Essential |
| Local optimum problem | Can get stuck | Can escape with some probability |
| Temperature | Not required | Required |
| Exploration | Usually more restricted | Controlled by temperature |

**Exam question:** Why is Simulated Annealing better than ordinary Hill Climbing?

**Answer:** Ordinary Hill Climbing generally accepts only improving neighboring solutions and can become trapped in local optima. Simulated Annealing sometimes accepts worse solutions using a temperature-dependent probability. This allows it to explore other regions of the search space and potentially find a better global solution.

---

# PART 2: EVOLUTIONARY ALGORITHMS AND GENETIC ALGORITHMS

*(PDF pages 5–17)*

## 7. Introduction to Evolutionary Algorithms

Your professor introduces Evolutionary Algorithms on page 5 using the concept of biological evolution.

To understand this topic, first understand natural selection.

### 7.1 What is Natural Selection?

Natural selection is a biological process in which organisms with characteristics better suited to their environment are more likely to survive and reproduce.

Over successive generations, useful characteristics become more common in the population.

Consider a simple example.

Suppose there are two types of animals:

- Animals that run slowly.
- Animals that run quickly.

If predators are present, faster animals may have a higher chance of survival.

They may reproduce and pass their characteristics to their offspring.

Over many generations, the population may contain more fast-running animals.

This is the basic inspiration behind Evolutionary Algorithms.

### 7.2 What are Evolutionary Algorithms?

Evolutionary Algorithms (EAs) are population-based optimization techniques inspired by biological evolution.

Instead of maintaining only one candidate solution, they maintain a population of candidate solutions.

They repeatedly apply operations inspired by evolution to produce better solutions.

The general process is:

1. Create an initial population.
2. Evaluate the fitness of each individual.
3. Select individuals for reproduction.
4. Generate offspring.
5. Introduce mutations.
6. Form a new population.
7. Repeat until a stopping condition is satisfied.

### 7.3 Understanding Important Terminology

| Biological Term | Evolutionary Algorithm Meaning |
|---|---|
| Population | Collection of candidate solutions |
| Individual | One candidate solution |
| Chromosome | Representation of a solution |
| Gene | One part of a chromosome |
| Fitness | Quality of a candidate solution |
| Parent | Selected individual used for reproduction |
| Offspring | Newly generated solution |
| Generation | One iteration of population evolution |
| Mutation | Random modification of a solution |
| Crossover | Combining information from parents |

### Example

Suppose we want to maximize:

\[
f(x)=x^2
\]

Where:

\[
0\leq x\leq31
\]

We can represent each value using five binary bits.

For example:

| Individual | Binary Representation | Decimal Value | Fitness |
|---|---|---:|---:|
| A | 00101 | 5 | 25 |
| B | 01010 | 10 | 100 |
| C | 10000 | 16 | 256 |
| D | 11100 | 28 | 784 |

Here, individual D has the highest fitness.

An evolutionary algorithm will give better individuals a higher chance of contributing to future generations.

Eventually, it may discover:

\[
x=31
\]

With:

\[
f(31)=961
\]

This is the optimal solution for this particular problem.

---

## 8. Genetic Algorithm (GA)

Genetic Algorithm is one of the most popular Evolutionary Algorithms.

Your professor's slide on page 7 states that GA is:

- Based on natural selection and genetics.
- Theoretically and empirically proven to provide robust search in complex environments.
- Composed of three major operators:
  1. Reproduction.
  2. Crossover.
  3. Mutation.

Let's understand each operator.

## 9. Operator 1: Reproduction (Selection)

### 9.1 What is Reproduction?

Reproduction is the process of selecting individuals from the current population according to their fitness values.

Individuals with higher fitness generally have a higher probability of being selected as parents.

The basic idea is:

**Survival of the fittest.**

Your professor explains this on page 8.

### 9.2 What is a Fitness Function?

A fitness function measures how good a candidate solution is for the given problem.

It helps the algorithm compare different individuals.

For example:

Suppose we want to maximize:

\[
f(x)=x^2
\]

The fitness of an individual represented by \(x=5\) is:

\[
f(5)=25
\]

The fitness of another individual represented by \(x=10\) is:

\[
f(10)=100
\]

Therefore, the second individual has better fitness.

### 9.3 Fitness-Based Selection

One common method is Roulette Wheel Selection.

The probability of selecting an individual is:

\[
\boxed{P_i=\frac{f_i}{\sum_{j=1}^{N}f_j}}
\]

Where:

- \(P_i\) = Probability of selecting individual \(i\).
- \(f_i\) = Fitness of individual \(i\).
- \(N\) = Population size.

### 9.4 Numerical Example: Roulette Wheel Selection

Suppose the population contains four individuals.

| Individual | Fitness |
|---|---:|
| P1 | 24 |
| P2 | 23 |
| P3 | 20 |
| P4 | 11 |

Total fitness:

\[
F=24+23+20+11
\]

\[
F=78
\]

Now calculate selection probabilities.

For P1:

\[
P_1=\frac{24}{78}=0.3077
\]

For P2:

\[
P_2=\frac{23}{78}=0.2949
\]

For P3:

\[
P_3=\frac{20}{78}=0.2564
\]

For P4:

\[
P_4=\frac{11}{78}=0.1410
\]

Therefore:

| Individual | Fitness | Selection Probability |
|---|---:|---:|
| P1 | 24 | 30.77% |
| P2 | 23 | 29.49% |
| P3 | 20 | 25.64% |
| P4 | 11 | 14.10% |

Notice that the individual with fitness 24 has a higher probability of selection than the individual with fitness 11.

However, a lower-fitness individual can also be selected.

This is important because it maintains diversity in the population.

### 9.5 How Roulette Wheel Selection Works

Imagine a roulette wheel divided into sections.

Each individual gets a section proportional to its selection probability.

An individual with higher fitness gets a larger section.

We spin the wheel randomly, and whichever section is selected becomes a parent.

The process is repeated to select the required number of parents.

**Important:** Selection probability does not guarantee selection. A high-fitness individual can be missed in one selection, while a low-fitness individual can be selected.

---

## 10. Operator 2: Crossover

### 10.1 What is Crossover?

Crossover is the process of combining genetic information from two parent individuals to generate new offspring.

It is inspired by genetic recombination in biological reproduction.

Your professor explains crossover on pages 10–12.

### 10.2 Single-Point Crossover

This is the simplest crossover technique.

Steps:

1. Select two parent chromosomes.
2. Randomly select a crossover position.
3. Divide both chromosomes at that position.
4. Exchange the parts after the crossover position.
5. Generate two offspring.

### 10.3 Numerical Example

Suppose we have two parent chromosomes:

\[
P_1=110|010
\]

\[
P_2=001|111
\]

The vertical line represents the crossover point.

Separate each chromosome:

Parent 1:

- Left part = 110
- Right part = 010

Parent 2:

- Left part = 001
- Right part = 111

Now exchange the right parts.

Offspring 1:

\[
C_1=110|111
\]

Offspring 2:

\[
C_2=001|010
\]

Therefore:

| Parent | Chromosome |
|---|---|
| P1 | 110010 |
| P2 | 001111 |

After crossover:

| Offspring | Chromosome |
|---|---|
| C1 | 110111 |
| C2 | 001010 |

The offspring contain genetic information from both parents.

### 10.4 Understanding Your Professor's Diagram

On page 12, your professor shows decimal-digit chromosomes:

Parent 1:

\[
327|52411
\]

Parent 2:

\[
247|48552
\]

After single-point crossover:

\[
C_1=32748552
\]

\[
C_2=24752411
\]

The first three digits remain unchanged, while the remaining digits are exchanged.

### 10.5 Crossover Probability

Crossover is often controlled using crossover probability:

\[
P_c
\]

For example:

\[
P_c=0.8
\]

This means crossover is performed with probability 80% when a pair of parents is considered.

It does not mean that 80% of the genes are exchanged.

If crossover is not performed, the selected parents may simply be copied to the offspring population.

### 10.6 Types of Crossover

Apart from single-point crossover, other common methods are:

**Two-Point Crossover**

Two crossover positions are selected, and the section between them is exchanged.

**Uniform Crossover**

Each gene is independently selected from either parent according to a random mask.

**Important examination point:** The suitable crossover method depends on the representation of the solution. For example, ordinary binary crossover may not preserve valid permutations in problems such as TSP.

---

## 11. Operator 3: Mutation

### 11.1 What is Mutation?

Mutation is the occasional random modification of one or more genes in a chromosome.

Your professor explains this on page 13.

Why do we need mutation?

Consider what happens if we only use reproduction and crossover.

After several generations, individuals may become very similar.

The population may lose genetic diversity.

Consequently, the algorithm may stop exploring new regions of the search space.

Mutation helps introduce new genetic information.

### 11.2 Example: Binary Mutation

Suppose the chromosome is:

\[
C=110010
\]

Assume we randomly select the fourth position for mutation.

The original bit is:

\[
0
\]

We flip it to:

\[
1
\]

The new chromosome becomes:

\[
\boxed{C'=110110}
\]

In binary representation, mutation commonly means:

\[
0\rightarrow1
\]

or:

\[
1\rightarrow0
\]

### 11.3 Example from Your Professor's Notes

On page 14, the professor shows chromosomes represented using decimal digits.

For example:

\[
32748552
\]

After mutation, one of the digits changes:

\[
32748152
\]

Only one position is modified.

This illustrates the basic concept of mutation.

### 11.4 Mutation Probability

Mutation is generally performed with a small probability.

Let:

\[
P_m=0.01
\]

This represents a mutation probability of 1% per gene, if the implementation defines mutation at the gene level.

A low mutation probability helps maintain diversity without completely destroying useful genetic information.

### 11.5 What Happens if Mutation Probability Is Too High?

If mutation probability is extremely high:

- Useful genetic information may be destroyed.
- Offspring may become almost random.
- The algorithm may struggle to preserve good solutions.

If mutation probability is too low:

- The population may lose diversity.
- The algorithm may become trapped in a local optimum.
- Exploration may become insufficient.

Therefore, mutation probability must be selected carefully.

---

## 12. Complete Working of a Genetic Algorithm

Now let's combine reproduction, crossover, and mutation.

Suppose we want to maximize:

\[
f(x)=x^2
\]

Where:

\[
0\leq x\leq31
\]

We use five-bit binary chromosomes.

### Step 1: Initial Population

Suppose the initial population is:

| Individual | Chromosome | Decimal | Fitness |
|---|---|---:|---:|
| P1 | 00101 | 5 | 25 |
| P2 | 01010 | 10 | 100 |
| P3 | 10000 | 16 | 256 |
| P4 | 11100 | 28 | 784 |

### Step 2: Calculate Fitness

The fitness function is:

\[
f(x)=x^2
\]

Therefore, calculate the fitness of each individual.

The highest fitness is 784.

### Step 3: Reproduction

Select parents according to their fitness.

Suppose P3 and P4 are selected.

\[
P_3=10000
\]

\[
P_4=11100
\]

### Step 4: Crossover

Choose the second bit as the crossover point.

\[
P_3=10|000
\]

\[
P_4=11|100
\]

Exchange the parts after the crossover point.

\[
C_1=10100
\]

\[
C_2=11000
\]

### Step 5: Mutation

Suppose the third bit of the first offspring changes.

Before mutation:

\[
C_1=10100
\]

After mutation:

\[
C_1=10000
\]

### Step 6: Create the Next Generation

The offspring are evaluated, and a new population is formed.

The process continues until:

- A sufficiently good solution is found.
- A maximum number of generations is reached.
- A stopping condition is satisfied.

### Complete GA Flow

```text
       Initial Population
               |
               v
        Fitness Evaluation
               |
               v
          Reproduction
          (Selection)
               |
               v
           Crossover
               |
               v
            Mutation
               |
               v
        New Population
               |
               v
       Stopping Condition?
          /         \
        No           Yes
        |              |
        v              v
   Repeat          Best Solution
```

---

## 13. Other Important Genetic Algorithm Concepts

Your professor introduces additional concepts on pages 15–17.

### 13.1 Population-Based Method

Unlike Hill Climbing and Simulated Annealing, which generally maintain one current solution, Genetic Algorithms maintain multiple candidate solutions simultaneously.

For example:

\[
Population=\{S_1,S_2,S_3,S_4,S_5\}
\]

All five individuals represent different candidate solutions.

The algorithm evaluates and evolves the population.

This allows it to explore multiple regions of the search space at the same time.

### 13.2 Non-Derivative Method

Your professor's handwritten annotation on page 15 mentions that GA is a non-derivative method.

This is important.

Gradient-based optimization algorithms require derivatives of the objective function.

For example:

\[
f(x)=x^2
\]

Its derivative is:

\[
f'(x)=2x
\]

However, Genetic Algorithms do not require this derivative.

They only require a fitness function that can evaluate candidate solutions.

This makes them useful when:
- The objective function is discontinuous.
- The objective function is non-differentiable.
- The search space is discrete.
- Derivatives are unavailable or difficult to calculate.

### 13.3 Elitism

Elitism is the practice of directly preserving the best individuals from the current generation into the next generation.

Example:

Suppose the current population has fitness values:

\[
10,\ 20,\ 50,\ 30
\]

The best individual has fitness 50.

With elitism, we directly copy this individual to the next generation.

Why?

Because crossover and mutation may accidentally destroy the best solution.

Elitism helps prevent the loss of the best solution discovered so far.

### 13.4 Culling

Culling means removing individuals from the population.

For example, suppose the population size is five, but the algorithm generates ten offspring.

We must select which individuals will survive in the next generation.

Some individuals are removed to maintain the required population size.

### 13.5 Important GA Parameters

Your professor summarizes the important components on page 16.

| Parameter | Meaning |
|---|---|
| Population size | Number of individuals |
| Representation | How each solution is encoded |
| Fitness function | Measures solution quality |
| Selection method | Determines which individuals become parents |
| Recombination | Determines how parents generate offspring |
| Mutation rate | Controls random modifications |
| Elitism | Preserves the best individuals |
| Culling | Removes individuals |

### 13.6 Genetic Algorithm Pseudocode

Your professor provides the GA algorithm on page 17.

The simplified form is:

```text
function GENETIC-ALGORITHM(population, fitness):

    repeat:

        weights = calculate fitness weights

        new_population = empty list

        for i = 1 to population size:

            parent1, parent2 = select two parents

            child = crossover(parent1, parent2)

            with small probability:
                child = mutate(child)

            add child to new_population

        population = new_population

    until stopping condition

    return best individual
```

Let's understand the important operations.

**Weighted selection:** Better individuals receive a higher probability of selection.

**Reproduce:** Two selected parents generate an offspring.

**Mutation:** Randomly modifies the offspring with a small probability.

**Population replacement:** The newly generated population becomes the current population.

**Termination:** The algorithm stops when a sufficiently good solution is found or the allowed time/generations are exhausted.

---

## 14. Simulated Annealing vs Genetic Algorithm

This comparison is particularly useful for examinations.

| Feature | Simulated Annealing | Genetic Algorithm |
|---|---|---|
| Search approach | Local search | Population-based search |
| Inspiration | Physical annealing | Biological evolution |
| Number of current solutions | Generally one | Multiple |
| Main mechanism | Probabilistic acceptance | Selection, crossover, mutation |
| Randomness | Yes | Yes |
| Local optima | Can escape by accepting worse solutions | Can explore different regions using a population |
| Temperature | Required | Not required |
| Derivatives | Not required | Not required |
| Main control parameters | Initial temperature, cooling schedule | Population size, crossover and mutation rates |

### Important Exam Question

**Q. Why is Genetic Algorithm called an evolutionary algorithm?**

Answer:

Genetic Algorithm is called an evolutionary algorithm because it is inspired by biological evolution and natural selection. It maintains a population of candidate solutions and improves them over successive generations using fitness-based selection, crossover, and mutation.

---

## 15. Applications of Genetic Algorithms

Your professor includes a photograph of the NASA ST5 spacecraft antenna on page 6.

This is an example of evolutionary optimization being used in engineering design.

The NASA ST5 mission used an evolutionary approach to design an antenna with a complex, unconventional shape.

Other applications include:

1. Engineering design optimization.
2. Scheduling and timetabling.
3. Travelling Salesperson Problem.
4. Feature selection in machine learning.
5. Neural network parameter optimization.
6. Resource allocation.
7. Robotics.
8. Circuit design.

**Remember:** Genetic Algorithms are especially useful when the search space is large, complex, or difficult to optimize using traditional gradient-based methods.

---

# PART 3: NON-DETERMINISTIC ACTIONS AND AND-OR SEARCH

*(PDF pages 18–22)*

## 16. Understanding Deterministic Environments

Before understanding non-deterministic actions, we need to understand deterministic actions.

### 16.1 What is a Deterministic Action?

An action is deterministic when performing the same action in the same state always produces the same next state.

Mathematically:

\[
Result(s,a)=s'
\]

Where:

- \(s\) = Current state.
- \(a\) = Action.
- \(s'\) = Next state.

There is only one predictable outcome.

### Example

Suppose a robot is at position A.

It performs the action:

\[
Move\ Right
\]

It always reaches position B.

Therefore:

\[
Result(A,Right)=B
\]

If the robot knows the environment, it can calculate a sequence of actions that reaches the goal.

For example:

\[
A\rightarrow B\rightarrow C\rightarrow G
\]

This sequence is the solution plan.

### 16.2 What is a Solution Plan?

A solution plan is a sequence of actions that takes an agent from its initial state to a goal state.

For example:

```text
Initial State: A

Actions:
1. Move Right
2. Move Right
3. Move Up

Goal State: G
```

In deterministic environments, this sequence is sufficient because the outcome of each action is predictable.

---

## 17. What are Non-Deterministic Actions?

An action is non-deterministic when performing the same action in the same state can produce multiple possible outcomes.

Mathematically:

\[
Result(s,a)=\{s_1,s_2,\ldots,s_n\}
\]

Instead of one next state, we have multiple possible next states.

### Example: Vacuum Cleaner

Suppose a vacuum cleaner is in a room containing dirt.

It performs the action:

\[
Clean
\]

Due to uncertainty in the environment, the result might be:

- State 1: The room becomes clean.
- State 2: The room remains dirty.

Therefore:

\[
Result(s,Clean)=\{s_1,s_2\}
\]

The agent cannot predict exactly which state will occur.

This creates a problem.

A fixed sequence of actions may fail because the actual state may differ from the expected state.

### 17.1 Why Do We Need a Contingency Plan?

A contingency plan is a plan that specifies what the agent should do depending on which outcome actually occurs.

For example:

```text
Perform Clean

If room becomes clean:
    Move Right

If room remains dirty:
    Perform Clean again
```

Unlike a fixed action sequence, a contingency plan adapts to different possible outcomes.

Your professor introduces this concept on page 18.

---

## 18. AND-OR Search Trees

AND-OR Search is a search technique used for problems involving non-deterministic actions.

It represents both:

- Choices made by the agent.
- Different outcomes that may occur in the environment.

There are two important types of nodes.

### 18.1 OR Nodes

An OR node represents a decision by the agent.

The agent can select one of the available actions.

For example, suppose a robot has three available actions:

- Move Left.
- Move Right.
- Clean.

The agent needs to choose one action.

If at least one action leads to a successful plan, the OR node can be considered solvable.

**Remember: OR = Agent's choice.**

### 18.2 AND Nodes

An AND node represents the possible outcomes of a non-deterministic action.

The agent does not control which outcome occurs.

It must prepare for every possible outcome.

For an AND node to be successfully solved, all its possible outcomes must have successful plans.

**Remember: AND = All possible outcomes must be handled.**

### 18.3 Difference Between AND and OR Nodes

| OR Node | AND Node |
|---|---|
| Represents a choice of action | Represents possible outcomes |
| Agent chooses one action | Environment determines the outcome |
| At least one successful child is sufficient | Every possible child must be successful |
| Represents decision-making | Represents uncertainty |

### 18.4 Understanding Your Professor's Vacuum Cleaner Example

On page 20, your professor shows eight possible states.

The available actions are:

- Clean.
- Right.
- Left.

The slide specifically states:

For state 1:

\[
Clean(1)=\{5,7\}
\]

For state 2:

\[
Clean(2)=\{4,8\}
\]

This means that cleaning in state 1 may produce either state 5 or state 7.

Similarly, cleaning in state 2 may produce state 4 or state 8.

The agent must prepare for both outcomes.

This is exactly why AND nodes are required.

### 18.5 Understanding the AND-OR Search Tree on Page 21

The diagram on page 21 shows a solution tree for the vacuum-cleaner problem.

Important observations:

1. The root represents the initial state.
2. Action choices are represented using OR nodes.
3. Different possible results are represented using AND nodes.
4. Some branches reach goal states.
5. Some branches reach loops.
6. A valid solution must account for every possible outcome of the selected actions.

The diagram also illustrates why simply finding one path to a goal is not enough.

In a non-deterministic environment, the plan must work regardless of which possible outcome occurs.

### 18.6 What is a Solution in AND-OR Search?

Your professor states that a solution is a subtree.

This is important.

In ordinary search, a solution is generally a path:

\[
S\rightarrow A\rightarrow B\rightarrow G
\]

In AND-OR Search, the solution may contain multiple branches.

Every possible outcome must eventually reach a goal state.

The solution is therefore a conditional plan.

---

## 19. AND-OR Search Algorithm

Your professor provides the pseudocode on page 22.

It contains two important functions:

1. OR-SEARCH.
2. AND-SEARCH.

Let's understand them.

### 19.1 OR-SEARCH

```text
function OR-SEARCH(problem, state, path):

    if state is goal:
        return empty plan

    if state creates a cycle:
        return failure

    for each action in available actions:

        plan = AND-SEARCH(
            problem,
            results(state, action),
            path
        )

        if plan is not failure:
            return action + plan

    return failure
```

**Explanation:**

First, check whether the current state is a goal.

If yes, return an empty plan because no additional action is required.

Next, check for cycles.

If the state is already present in the current path, return failure to prevent infinite looping.

Then examine the available actions.

For each action, call AND-SEARCH to verify whether all possible outcomes can be solved.

If a successful plan is found, return the selected action and its corresponding conditional plan.

Otherwise, return failure.

### 19.2 AND-SEARCH

```text
function AND-SEARCH(problem, states, path):

    for each state in states:

        plan = OR-SEARCH(problem, state, path)

        if plan is failure:
            return failure

    return conditional plan for all states
```

**Explanation:**

AND-SEARCH receives a set of possible outcomes.

It checks every possible state by calling OR-SEARCH.

If even one possible outcome cannot reach the goal, the entire action is considered unsuccessful.

If all outcomes have successful plans, return the conditional plan.

### 19.3 Important Difference Between the Two Functions

| OR-SEARCH | AND-SEARCH |
|---|---|
| Receives one state | Receives multiple possible states |
| Explores available actions | Explores all possible outcomes |
| Finds one successful action | Requires every outcome to be solvable |
| Returns an action and plan | Returns a conditional plan |

### 19.4 Important Exam Question

**Q. Why do we need AND-OR Search instead of ordinary BFS or DFS in non-deterministic environments?**

Answer:

Ordinary BFS and DFS generally construct paths by selecting a sequence of actions and assuming that each action has a predictable result. In non-deterministic environments, an action may produce multiple possible outcomes. Therefore, a successful solution must account for all possible outcomes. AND-OR Search represents the agent's choices using OR nodes and the environment's possible outcomes using AND nodes, allowing it to construct a conditional plan.

---

# PART 4: PARTIALLY OBSERVABLE ENVIRONMENTS AND BELIEF STATES

*(PDF pages 23–26)*

## 20. What is a Partially Observable Environment?

To understand this topic, first understand observability.

### 20.1 Fully Observable Environment

An environment is fully observable when the agent can obtain complete information about the current state through its sensors.

Example:

Suppose a robot is moving inside a room.

It has a perfect camera and can identify:
- Its current location.
- The position of obstacles.
- The position of other objects.
- Its surroundings.

It knows the complete current state.

This is a fully observable environment.

### 20.2 Partially Observable Environment

An environment is partially observable when the agent cannot determine the complete current state using the available percepts or sensors.

Your professor defines it on page 23 as:

The agent cannot completely determine the state description with the given percepts.

Example:

Imagine a robot vacuum cleaner operating in a house.

It can observe only the room it is currently inside.

It does not know:
- Whether another room is dirty.
- Whether an obstacle exists behind a wall.
- Whether another room has been cleaned.

The robot has incomplete information about the environment.

This is a partially observable environment.

### 20.3 More Examples

**Self-driving car:**

A car has cameras and sensors, but it cannot always observe everything.

For example, another vehicle may be hidden behind a large truck.

**Medical diagnosis:**

A doctor cannot directly observe the complete internal condition of a patient.

Instead, the doctor uses:
- Symptoms.
- Medical history.
- Test results.

These observations provide incomplete information about the actual condition.

**Robot navigation:**

A robot may know its approximate location but not its exact position because of sensor errors.

---

## 21. What are Belief States?

This is the most important concept in partially observable search.

### 21.1 Why Do We Need Belief States?

Suppose a robot is moving in a building.

It receives an observation that does not tell it exactly which room it is in.

It knows that it might be in:

\[
S_1,\ S_2,\ \text{or }S_3
\]

It cannot select only one state because it does not have enough information.

Instead, it maintains all possible states.

This collection is called a belief state.

### 21.2 Definition

A belief state is the agent's current belief about the possible physical states of the environment, given the sequence of actions and percepts received so far.

Your professor provides this definition on page 23.

Mathematically:

\[
\boxed{B=\{s_1,s_2,\ldots,s_n\}}
\]

Where:
- \(B\) = Belief state.
- \(s_i\) = A possible physical state.

**Important:** In classical belief-state search, a belief state can be represented as a set of possible states. In probabilistic models, we can also associate probabilities with these states.

### 21.3 Numerical Example

Suppose a robot can be in any one of four rooms:

\[
S=\{A,B,C,D\}
\]

Initially, the robot does not know its location.

Therefore:

\[
B_0=\{A,B,C,D\}
\]

Now the robot receives a sensor observation.

It discovers that it must be in either room A or room B.

The updated belief state becomes:

\[
B_1=\{A,B\}
\]

Later, it receives another observation that confirms it is in room B.

Therefore:

\[
B_2=\{B\}
\]

Notice how the belief state becomes smaller as the robot obtains more information.

---

## 22. Constructing Belief-State Search

Your professor explains this on pages 25–26.

Suppose an original problem has \(N\) physical states.

We want to construct a new search problem in which each state represents a set of possible physical states.

### 22.1 State Space

The professor states:

\[
\boxed{\text{Belief States}=\text{Power Set of }N\text{ States}}
\]

What does this mean?

The power set of a set is the collection of all its possible subsets.

Suppose:

\[
S=\{A,B\}
\]

Its power set is:

\[
P(S)=\{\emptyset,\{A\},\{B\},\{A,B\}\}
\]

Therefore, if the original problem has \(N\) states, the total number of possible belief states is:

\[
\boxed{2^N}
\]

This is an important mathematical result.

### 22.2 Numerical Example

Suppose the original problem has three states:

\[
S=\{A,B,C\}
\]

The possible belief states are:

\[
\emptyset
\]

\[
\{A\},\{B\},\{C\}
\]

\[
\{A,B\},\{A,C\},\{B,C\}
\]

\[
\{A,B,C\}
\]

Total:

\[
1+3+3+1=8
\]

Using the formula:

\[
2^3=8
\]

Therefore, the belief-state space contains eight possible subsets.

**Exam tip:** Remember that the belief-state space can grow exponentially with the number of physical states.

### 22.3 Initial Belief State

Your professor states that the initial belief state is the set of all physical states.

Therefore:

\[
\boxed{B_0=S}
\]

If the original state space is:

\[
S=\{A,B,C,D\}
\]

Then:

\[
B_0=\{A,B,C,D\}
\]

This represents complete initial uncertainty.

In general, a particular problem may provide a more restricted initial belief state.

---

## 23. Action Space in Belief-State Search

Your professor explains two possibilities on page 25.

The available actions depend on the actions that are valid in the possible physical states.

### Case 1: Union of Actions

Suppose:

State A allows:

\[
Actions(A)=\{Left,Right\}
\]

State B allows:

\[
Actions(B)=\{Right,Up\}
\]

If actions can be selected based on the actual state or the agent has a mechanism to handle state-dependent validity, the possible action collection may be:

\[
\{Left,Right,Up\}
\]

This is the union:

\[
Actions(A)\cup Actions(B)
\]

### Case 2: Intersection of Actions

If the agent must choose one action that is valid in every possible physical state, then it must use the intersection.

\[
Actions(A)\cap Actions(B)
\]

Therefore:

\[
\{Left,Right\}\cap\{Right,Up\}
\]

\[
=\{Right\}
\]

Only Right is valid in both states.

**Important distinction:** The union represents actions available in at least one possible state. The intersection represents actions available in all possible states. The appropriate choice depends on the problem's action-validity assumptions.

---

## 24. Transition Model in Belief-State Search

A transition model tells us which states can be reached after performing an action.

Your professor explains two cases on page 26.

### 24.1 Deterministic Action

Suppose:

\[
B=\{A,B\}
\]

The agent performs action Right.

Assume:

\[
Result(A,Right)=C
\]

\[
Result(B,Right)=D
\]

The new belief state becomes:

\[
\boxed{B'=\{C,D\}}
\]

### 24.2 Non-Deterministic Action

Suppose:

\[
Result(A,Right)=\{C,D\}
\]

And:

\[
Result(B,Right)=\{E,F\}
\]

The new belief state is the union of all possible outcomes:

\[
B'=\{C,D\}\cup\{E,F\}
\]

Therefore:

\[
\boxed{B'=\{C,D,E,F\}}
\]

### 24.3 Prediction Step

Your professor calls the process of generating a new belief state after an action the **Prediction Step**.

In simple words:

The agent predicts all states that might be reached after executing an action.

Mathematically, for a belief state \(B\) and action \(a\):

\[
\boxed{
B'=\bigcup_{s\in B}Result(s,a)
}
\]

This formula assumes the action is applicable in every state in \(B\).

---

## 25. Goal Test in Belief-State Search

This is a very important difference between ordinary search and belief-state search.

Your professor states:

A belief state satisfies the goal only if all the physical states in it satisfy the goal test.

Mathematically:

\[
\boxed{Goal(B)=True}
\]

Only if:

\[
\forall s\in B,\ Goal(s)=True
\]

The symbol \(\forall\) means "for all".

### Example

Suppose:

\[
B=\{A,B,C\}
\]

Assume:
- A is a goal state.
- B is a goal state.
- C is not a goal state.

Is the belief state a goal?

No.

Because:

\[
Goal(C)=False
\]

Every possible state must satisfy the goal condition.

Now suppose:

\[
B=\{A,B\}
\]

And both A and B are goal states.

Then:

\[
Goal(B)=True
\]

### Why Is This Necessary?

Imagine a robot that believes it might be in either a clean room or a dirty room.

It cannot declare the cleaning task completed merely because one possible state is clean.

It must be certain that every possible state satisfies the goal.

---

## 26. Path Cost in Belief-State Search

Your professor mentions that path cost is tricky.

Why?

Because one action may affect multiple possible physical states.

For example:

\[
B=\{A,B\}
\]

Suppose the action Right has:

\[
Cost(A,Right)=2
\]

\[
Cost(B,Right)=5
\]

What is the cost of performing Right?

There is no single universally correct answer without specifying how the problem measures cost.

Possible approaches include:

1. Average cost.
2. Maximum cost.
3. Worst-case cost.
4. Expected cost, if probabilities are available.

For example, if we use average cost:

\[
Cost=\frac{2+5}{2}=3.5
\]

If we use worst-case cost:

\[
Cost=\max(2,5)=5
\]

The correct method depends on the assumptions of the problem.

### 26.1 Summary of Belief-State Search

| Component | Description |
|---|---|
| State space | Power set of physical states |
| Initial state | Set of possible initial physical states |
| Action space | Union or intersection, depending on assumptions |
| Transition model | Generates all possible successor states |
| Prediction step | Updates the belief state after an action |
| Goal test | Every physical state must satisfy the goal |
| Path cost | Depends on how costs across possible states are combined |

### 26.2 Important Examination Question

**Q. Why does belief-state search have an exponential state space?**

Answer:

If the original problem contains \(N\) physical states, a belief state can represent any subset of those states. The number of subsets of an \(N\)-element set is \(2^N\). Therefore, the belief-state search space can contain up to \(2^N\) states, making its size exponential in the original number of physical states.

---

# PART 5: ONLINE SEARCH AND UNKNOWN ENVIRONMENTS

*(PDF pages 27–30)*

## 27. Offline Search vs Online Search

Before studying Online Search, understand Offline Search.

### 27.1 Offline Search

In offline search, the agent has access to a known model of the environment before taking actions.

It can calculate a plan in advance.

For example:

Suppose a robot knows the complete map of a building.

It can calculate:

\[
Start\rightarrow A\rightarrow B\rightarrow Goal
\]

It computes the complete path first and then executes it.

This is offline search.

### 27.2 Online Search

In online search, the environment is initially unknown.

The agent must explore the environment while making decisions.

Your professor defines online search on page 27 as:

**Online search interleaves computations and actions.**

This means the agent does not calculate the complete solution before acting.

Instead, it follows this process:

1. Observe the environment.
2. Decide what to do.
3. Perform an action.
4. Receive a new percept.
5. Update its knowledge.
6. Decide the next action.

### 27.3 Example: Robot in an Unknown Building

Imagine a robot placed inside a building.

It knows:
- Its starting position.
- Its available actions.

But it does not know the complete building layout.

It starts moving.

When it reaches a new location, it discovers:
- Whether a path exists.
- Whether an obstacle is present.
- Which directions are available.

It gradually builds a map.

This is online search.

### 27.4 Offline vs Online Search

| Feature | Offline Search | Online Search |
|---|---|---|
| Environment | Known | Initially unknown |
| Complete map | Available | Built during exploration |
| Planning | Before execution | During execution |
| Actions | Usually after planning | Interleaved with planning |
| New information | Not required for the known model | Continuously acquired |
| Example | Route planning with a known map | Robot exploring an unknown building |

### 27.5 Important Assumptions in Your Lecture

Your professor makes two assumptions on page 27:

1. The environment is fully observable.
2. The environment is deterministic.

Notice that an environment can be unknown but still fully observable and deterministic.

These are different properties.

**Unknown:** The agent does not know the environment's structure in advance.

**Fully observable:** Once the agent reaches a location, it can observe the complete relevant state there.

**Deterministic:** The same action in the same state produces the same outcome.

---

## 28. Competitive Ratio

This is an important mathematical concept from page 28.

### 28.1 What is Competitive Ratio?

Competitive ratio measures how well an online algorithm performs compared with an optimal offline algorithm.

Your professor defines it as:

\[
\boxed{
Competitive\ Ratio=
\frac{Actual\ Path\ Cost}{Shortest\ Path\ Cost}
}
\]

The actual path cost is the cost incurred by the online agent.

The shortest path cost represents the optimal cost that could have been achieved with complete knowledge of the environment.

### 28.2 Numerical Example

Suppose:

The shortest possible path from start to goal has a cost of:

\[
C^*=10
\]

However, an online agent does not know the environment.

It explores unnecessarily and finally reaches the goal with cost:

\[
C=25
\]

Therefore:

\[
Competitive\ Ratio=\frac{25}{10}
\]

\[
\boxed{Competitive\ Ratio=2.5}
\]

This means the online agent incurred 2.5 times the optimal path cost.

### 28.3 Another Example

Suppose:

\[
C=40
\]

\[
C^*=20
\]

Then:

\[
Competitive\ Ratio=\frac{40}{20}=2
\]

The algorithm is twice as expensive as the optimal offline solution.

### 28.4 Interpretation

Generally:

- Competitive ratio = 1 means optimal performance.
- Competitive ratio close to 1 means good performance.
- A larger ratio means more additional cost.
- Infinite competitive ratio means the algorithm may fail to reach the goal in a situation where an optimal route exists.

---

## 29. Reversible and Irreversible Actions

Your professor introduces this concept on page 28.

### 29.1 Reversible Actions

An action is reversible if the agent can return to its previous state.

Example:

A robot moves from A to B.

It can move back from B to A.

This is represented by an undirected connection:

\[
A\leftrightarrow B
\]

The agent can explore and backtrack.

### 29.2 Irreversible Actions

An action is irreversible if the agent cannot return to its previous state.

Example:

A robot moves from A to B.

But there is no action that takes it from B back to A.

This can be represented by a directed connection:

\[
A\rightarrow B
\]

The agent may enter a dead end.

### 29.3 Why Are Irreversible Actions Dangerous?

Suppose an agent is exploring an unknown environment.

It moves from A to B.

At B, it discovers that there is no path to the goal.

If the action was reversible, it could return to A and try another direction.

But if the action was irreversible, it may become permanently trapped.

Your professor notes that irreversible actions can make the competitive ratio infinite.

The reason is that the agent may incur unbounded relative cost or fail to reach the goal even when a feasible path exists for an agent with complete knowledge.

### 29.4 Reversible vs Irreversible

| Reversible | Irreversible |
|---|---|
| Can return to the previous state | Cannot return to the previous state |
| Easier to explore | Exploration is risky |
| Backtracking is possible | Backtracking may be impossible |
| Commonly represented by undirected edges | Commonly represented by directed edges |

### 29.5 Online Map Construction

Your professor also states that the agent augments its map with each new percept.

This means the agent continuously updates its internal representation of the environment.

For example:

Initially:

```text
S
```

After exploring:

```text
S ---- A
```

After further exploration:

```text
S ---- A
       |
       B
```

The map becomes more complete as the agent explores.

---

## 30. Online DFS (Online Depth-First Search)

Your professor provides the Online DFS pseudocode on page 29.

First, let's revise ordinary DFS.

### 30.1 What is DFS?

Depth-First Search is a graph-search algorithm that explores one branch as deeply as possible before backtracking.

Suppose we have:

```text
       A
      / \
     B   C
    / \
   D   E
```

Starting from A, DFS might visit:

\[
A\rightarrow B\rightarrow D
\]

Then it backtracks and visits E.

Finally, it explores C.

DFS uses a stack-like approach.

### 30.2 Why Do We Need Online DFS?

In ordinary DFS, the graph is already known.

In Online DFS, the agent does not initially know all the neighboring states.

It discovers available actions as it explores.

Therefore, it must remember its previous observations and actions.

### 30.3 Important Variables in Online DFS

Your professor's pseudocode maintains several data structures.

**1. Current state**

The state where the agent currently is.

**2. Previous state and action**

Used to remember how the agent reached its current location.

**3. Result table**

Stores the result of previously executed actions.

It maps:

\[
(state,action)\rightarrow next\ state
\]

**4. Untried table**

Stores actions that have not yet been attempted from each state.

**5. Unbacktracked table**

Stores previously visited states to which the agent has not yet returned.

These data structures allow the agent to explore systematically.

### 30.4 Working of Online DFS

The algorithm works approximately as follows:

**Step 1:** Observe the current state.

**Step 2:** Check whether it is the goal.

If yes, stop.

**Step 3:** If the state is new, discover its available actions.

**Step 4:** If the agent has arrived from another state, record the transition.

**Step 5:** Check whether unexplored actions remain.

If yes, choose one and execute it.

**Step 6:** If no unexplored actions remain, backtrack to a previously visited state.

**Step 7:** Continue until the goal is reached or no further exploration is possible.

### 30.5 Understanding the Pseudocode on Page 29

The important operations are:

```text
if problem.IS-GOAL(s'):
    return stop
```

Stop if the current state is the goal.

```text
if s' is a new state:
    untried[s'] = problem.ACTIONS(s')
```

Discover the available actions at a new state.

```text
result[s,a] = s'
```

Remember the outcome of an action.

```text
if untried[s'] is empty:
    ...# Styled Markdown Example

This is a paragraph with **bold** and *italic* text.

## Lists Example
- First item
- Second item with **bold**
- Nested item with *italic*
- Another nested item
- Third item

## Java Code Example
```javascript
function greeting(name) {
return `Hello, ${name}!`;
}
```

## Python Example
```python
def fibonacci(n):
if n <= 1:
    return n
else:
    a, b = 0, 1
    for _ in range(n - 1):
        a, b = b, a + b
    return b

# List comprehension example
squares = [x**2 for x in range(10)]
```  

## Blockquote Example
> This is a blockquote.
> It can span multiple lines.

## Table Example
| Feature | Description |
|---------|-------------|
| Tables  | Organized data display |
| Lists   | Bullet points and numbers |
| Code    | Syntax highlighted blocks |

## Link Example
[Visit GitHub](https://github.com)

***

### Cat Image Example
![Placeholder Image](https://images.unsplash.com/photo-1533743983669-94fa5c4338ec?q=80&w=800&auto=format&fit=crop&ixlib=rb-4.0.3&ixid=M3wxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8fA%3D%3D)
```

If no unexplored actions remain, the algorithm considers backtracking.

```text
a = POP(untried[s'])
```

Select an unexplored action.

The algorithm returns the selected action to the agent.

**Important:** Online DFS is not simply ordinary DFS with a different name. Its main challenge is that the agent must learn the environment while performing the search.

---

## 31. Online Local Search

Your professor introduces Online Local Search on page 30.

It discusses two approaches:

1. Hill Climbing.
2. Random Walk.

### 31.1 Online Hill Climbing

Hill Climbing is a local search algorithm in which the agent selects a neighboring state based on its local evaluation.

In an online setting, the agent discovers its neighboring states while exploring.

It does not necessarily know the complete environment in advance.

The algorithm generally moves towards a better neighboring state.

**Problem:**

Your professor specifically mentions:

It can still get stuck at a local optimum.

Example:

Suppose the agent is on a small hill.

All neighboring states have lower evaluation values.

It cannot identify a better immediate move.

It gets stuck, even though a better solution exists elsewhere.

### 31.2 Random Walk

Random Walk is an online exploration technique in which the agent selects an action randomly from the available actions.

For example:

Suppose the agent is at state A.

Available actions:

\[
\{Left,Right,Up,Down\}
\]

The algorithm randomly chooses one action.

It repeats this process at each new state.

Your professor mentions two important characteristics:

1. The agent should keep track of actions already tried.
2. It can take exponentially many steps to reach the goal.

### 31.3 Why Can Random Walk Take So Long?

Suppose the agent is moving through a large graph.

It may:
- Visit the same states repeatedly.
- Move away from the goal.
- Enter unproductive regions.
- Revisit previously explored locations.

Because the actions are selected randomly, there is no guarantee that the agent will consistently move towards the goal.

Therefore, the number of steps can become very large.

### 31.4 Understanding the Diagram on Page 30

The diagram shows a starting state S on the left and a goal state G on the right.

There are multiple intermediate states.

The arrows represent possible movements between states.

A random-walk agent may move:
- Towards the goal.
- Away from the goal.
- Back to previously visited states.

It must explore until it eventually reaches G.

### 31.5 Hill Climbing vs Random Walk

| Feature | Hill Climbing | Random Walk |
|---|---|---|
| Selection | Based on evaluation | Random |
| Uses local information | Yes | Yes |
| Goal-directed | Generally | Not necessarily |
| Can get stuck | Yes, at local optima | Can wander or revisit states |
| Exploration | Limited | Random exploration |
| Main limitation | Local optimum | Potentially very long exploration |

---

# PART 6: COMPLETE LECTURE REVISION

## 32. All Major Concepts at a Glance

Here is a consolidated revision of the entire lecture.

| Topic | Main Idea | Important Concept |
|---|---|---|
| Simulated Annealing | Accepts some worse solutions | Temperature |
| Evolutionary Algorithms | Improve a population over generations | Natural selection |
| Genetic Algorithm | Uses evolutionary operators | Reproduction, crossover, mutation |
| Reproduction | Selects parents | Fitness function |
| Crossover | Combines parent chromosomes | Recombination |
| Mutation | Randomly modifies genes | Diversity |
| Non-deterministic Actions | One action can have multiple outcomes | Contingency plan |
| AND-OR Search | Handles multiple possible outcomes | AND and OR nodes |
| Partially Observable Environment | Complete state is not directly known | Belief states |
| Belief-State Search | Searches over sets of possible states | Power set |
| Online Search | Explores while acting | Computation-action interleaving |
| Competitive Ratio | Compares online and offline costs | Actual cost / Optimal cost |
| Online DFS | Explores unknown environments systematically | Untried and unbacktracked actions |
| Online Hill Climbing | Uses neighboring evaluations | Local optimum |
| Random Walk | Selects random actions | Exploration |

---

## 33. Important Mathematical Formulas

These are the formulas I recommend memorizing from this lecture.

| Concept | Formula |
|---|---|
| Simulated Annealing acceptance probability | \(P=e^{\Delta E/T}\) |
| Cost difference in your professor's pseudocode | \(\Delta E=Value(current)-Value(next)\) |
| Exponential cooling schedule | \(T_t=T_0\alpha^t\) |
| Roulette Wheel Selection | \(P_i=\frac{f_i}{\sum_j f_j}\) |
| Number of belief states | \(2^N\) |
| Belief-state transition | \(B'=\bigcup_{s\in B}Result(s,a)\) |
| Belief-state goal test | \(\forall s\in B,\ Goal(s)=True\) |
| Competitive ratio | \(\frac{Actual\ Path\ Cost}{Shortest\ Path\ Cost}\) |

**Important clarification:** The Simulated Annealing probability formula above follows your professor's minimization convention. For maximization, the sign convention must be adjusted appropriately.

---

# PART 7: IMPORTANT EXAMINATION QUESTIONS

The following questions cover the concepts from all 30 pages. I've divided them according to the type of answer you may need to write.

## 34. Short-Answer Questions (2–3 Marks)

**Q1. What is Simulated Annealing?**

Simulated Annealing is a probabilistic local search algorithm inspired by physical annealing. It sometimes accepts worse solutions to escape local optima. The probability of accepting worse solutions decreases as temperature decreases.

**Q2. What is the role of temperature in Simulated Annealing?**

Temperature controls the probability of accepting worse solutions. High temperature encourages exploration, whereas low temperature makes the algorithm more selective.

**Q3. What is a local optimum?**

A local optimum is a solution that is better than its neighboring solutions but may not be the best solution in the entire search space.

**Q4. What is a fitness function?**

A fitness function evaluates the quality of an individual in a Genetic Algorithm. Higher fitness generally indicates a better candidate solution.

**Q5. What are the three main operators of Genetic Algorithms?**

1. Reproduction.
2. Crossover.
3. Mutation.

**Q6. What is elitism?**

Elitism is the technique of directly preserving the best individuals from the current generation into the next generation.

**Q7. What is mutation?**

Mutation is the random modification of one or more genes with a small probability to maintain genetic diversity.

**Q8. What is a non-deterministic action?**

An action is non-deterministic if it can produce multiple possible outcomes when executed in the same state.

**Q9. What is a contingency plan?**

A contingency plan specifies what actions an agent should take depending on the actual outcome of a non-deterministic action.

**Q10. What is the difference between AND and OR nodes?**

OR nodes represent the agent's choice of an action, whereas AND nodes represent all possible outcomes of a non-deterministic action.

**Q11. What is a belief state?**

A belief state represents the set of possible physical states in which an agent might currently be.

**Q12. What is the prediction step?**

It is the process of generating a new belief state by calculating all possible successor states after performing an action.

**Q13. What is online search?**

Online search is a technique in which an agent interleaves computation and action while exploring an initially unknown environment.

**Q14. Define competitive ratio.**

It is the ratio of the actual path cost incurred by an online algorithm to the optimal shortest path cost.

**Q15. What is Online DFS?**

Online DFS is a search technique that explores an unknown environment by discovering available actions, remembering previous transitions, and backtracking when necessary.

---

## 35. Long-Answer Questions (5–10 Marks)

These are particularly useful for preparing descriptive examination answers.

| No. | Question | Important pages |
|---|---|---|
| 1 | Explain Simulated Annealing with its mathematical formulation and algorithm. | 2–4 |
| 2 | Explain the role of temperature and the acceptance probability in Simulated Annealing. | 3–4 |
| 3 | Explain Genetic Algorithms and their biological inspiration. | 5–7 |
| 4 | Explain reproduction, crossover, and mutation with suitable examples. | 8–14 |
| 5 | Explain the complete working of a Genetic Algorithm with pseudocode. | 15–17 |
| 6 | Compare Simulated Annealing and Genetic Algorithms. | 2–17 |
| 7 | Explain non-deterministic actions and the need for contingency planning. | 18–19 |
| 8 | Explain AND-OR Search Trees with a suitable example. | 19–22 |
| 9 | Explain partially observable environments and belief states. | 23–24 |
| 10 | Explain the construction of belief-state search. | 25–26 |
| 11 | Explain online search and the competitive ratio. | 27–28 |
| 12 | Explain Online DFS with its algorithm. | 29 |
| 13 | Explain Online Local Search, Hill Climbing, and Random Walk. | 30 |

---

## 36. Important Numerical Problems to Practice

I recommend practicing these five types of problems.

### Problem 1: Simulated Annealing

Current cost:

\[
E_{current}=40
\]

Next cost:

\[
E_{next}=50
\]

Temperature:

\[
T=20
\]

Calculate the probability of accepting the next solution.

**Solution:**

\[
\Delta E=40-50=-10
\]

\[
P=e^{-10/20}
\]

\[
P=e^{-0.5}
\]

\[
\boxed{P=0.6065}
\]

Therefore, the probability of accepting the worse solution is 60.65%.

### Problem 2: Genetic Algorithm Selection

Fitness values:

\[
10,\ 20,\ 30,\ 40
\]

Total fitness:

\[
F=100
\]

Selection probabilities:

\[
P_1=\frac{10}{100}=0.1
\]

\[
P_2=\frac{20}{100}=0.2
\]

\[
P_3=\frac{30}{100}=0.3
\]

\[
P_4=\frac{40}{100}=0.4
\]

Final answer:

| Individual | Selection Probability |
|---|---:|
| P1 | 10% |
| P2 | 20% |
| P3 | 30% |
| P4 | 40% |

### Problem 3: Crossover

Parents:

\[
P_1=101|110
\]

\[
P_2=010|001
\]

After single-point crossover:

\[
C_1=101001
\]

\[
C_2=010110
\]

### Problem 4: Belief-State Space

Suppose the original problem has six physical states.

Find the maximum number of belief states.

\[
N=6
\]

\[
2^N=2^6
\]

\[
\boxed{64}
\]

### Problem 5: Competitive Ratio

Actual path cost:

\[
C=60
\]

Optimal path cost:

\[
C^*=15
\]

\[
Competitive\ Ratio=\frac{60}{15}
\]

\[
\boxed{4}
\]

The online algorithm incurs four times the optimal path cost.

---

# PART 8: CONCEPTS YOU MUST NOT CONFUSE

These distinctions are particularly important because examination questions often test conceptual understanding.

| Concepts | Main Difference |
|---|---|
| Local Maximum vs Global Maximum | Best among neighbors vs best overall |
| Hill Climbing vs Simulated Annealing | Generally rejects worse solutions vs sometimes accepts them |
| Reproduction vs Crossover | Selects parents vs combines parents |
| Crossover vs Mutation | Combines genetic material vs randomly modifies genetic material |
| AND vs OR Nodes | All outcomes must succeed vs one successful choice is sufficient |
| Deterministic vs Non-deterministic | One predictable outcome vs multiple possible outcomes |
| Fully Observable vs Partially Observable | Complete state information vs incomplete state information |
| Physical State vs Belief State | Actual environment state vs set of possible states |
| Offline vs Online Search | Plans using a known environment vs explores while acting |
| Reversible vs Irreversible | Can return to previous state vs cannot return |
| Online DFS vs Random Walk | Systematic exploration and backtracking vs random action selection |

---

# PART 9: MY RECOMMENDED STUDY PRIORITY

If you have limited time before your examination, I recommend the following order.

| Priority | Topic | What you should master |
|---|---|---|
| Very High | Simulated Annealing | Formula, numerical problems, pseudocode, temperature |
| Very High | Genetic Algorithm | Selection, crossover, mutation, complete numerical example |
| Very High | AND-OR Search | AND/OR nodes, contingency plans, pseudocode |
| Very High | Belief-State Search | Power set, prediction step, goal test |
| High | Online Search | Offline vs online, competitive ratio |
| High | Online DFS | Variables and pseudocode |
| Medium | Online Local Search | Hill Climbing vs Random Walk |
| Medium | Evolutionary Algorithms | Biological inspiration, elitism, culling |

## Final Understanding: What Is This Entire Lecture Trying to Teach?

There is a common connection between all the topics in this lecture.

The lecture is about how AI agents solve search and optimization problems when ordinary search techniques are insufficient.

It introduces different challenges and corresponding techniques:

**Challenge 1: Getting stuck in local optima**

Solution: Simulated Annealing and Evolutionary Algorithms.

**Challenge 2: Finding better solutions in a large search space**

Solution: Genetic Algorithms using selection, crossover, and mutation.

**Challenge 3: Actions can produce multiple possible outcomes**

Solution: AND-OR Search and contingency planning.

**Challenge 4: The agent cannot determine its exact current state**

Solution: Belief-State Search.

**Challenge 5: The environment is initially unknown**

Solution: Online Search, Online DFS, and Online Local Search.

This is the overall logical connection between the five sections of your professor's lecture.

---

### My advice for your examination

Do not just memorize the definitions.

Make sure you can independently solve:
1. A Simulated Annealing acceptance-probability numerical.
2. A Roulette Wheel Selection numerical.
3. A single-point crossover problem.
4. A belief-state power-set problem.
5. A competitive-ratio numerical.
6. An AND-OR Search problem involving multiple possible outcomes.

If you understand these six problem types and can explain the corresponding algorithms, you will have a strong understanding of this lecture.

**The notes above cover all 30 pages of your uploaded PDF**, including its diagrams, examples, mathematical concepts, handwritten annotations, and pseudocode. The additional examples and explanations are supplementary teaching material rather than additional claims from the slides.
