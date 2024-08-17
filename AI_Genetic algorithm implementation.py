import numpy as np
import random

# Global Variables
best_fitness = 0
best_solution = None

def fitness_function(chromosome):
    """Computes the fitness value of a chromosome."""
    x = chromosome_to_decimal(chromosome)
    return x * x

def initialize_population(population_size, chromosome_length):
    """Initializes the population with random binary strings."""
    return np.random.randint(2, size=(population_size, chromosome_length))

def chromosome_to_decimal(chromosome):
    """Converts a binary chromosome to decimal."""
    return int(''.join(map(str, chromosome)), 2)

def crossover(parent1, parent2, crossover_type):
    """Performs crossover between two parent chromosomes."""
    if crossover_type == 0:
        # One-point crossover
        crossover_point = random.randint(1, len(parent1) - 1)
    else:
        # Two-point crossover
        crossover_points = sorted(random.sample(range(1, len(parent1)), 2))
        crossover_point = crossover_points[0]

    child1 = np.concatenate((parent1[:crossover_point], parent2[crossover_point:]))
    child2 = np.concatenate((parent2[:crossover_point], parent1[crossover_point:]))
    return child1, child2

def mutation(chromosome, mutation_type):
    """Applies mutation to a chromosome."""
    mutation_point = random.randint(0, len(chromosome) - 1)

    if mutation_type == 0:  # Bit flip mutation
        chromosome[mutation_point] = 1 - chromosome[mutation_point]
    elif mutation_type == 1:  # Swap mutation
        swap_point = random.randint(0, len(chromosome) - 1)
        chromosome[mutation_point], chromosome[swap_point] = chromosome[swap_point], chromosome[mutation_point]

    return chromosome

def solution_node(population):
    """Finds the solution node with the highest fitness."""
    max_index = np.argmax([fitness_function(individual) for individual in population])
    return population[max_index], fitness_function(population[max_index])

def genetic_algorithm(pop_size, crossover_type=0, mutation_type=0, term_condition=1, iterations=100):
    """Runs a Genetic Algorithm to maximize the fitness function."""
    population_size = pop_size
    chromosome_length = 5
    population = initialize_population(population_size, chromosome_length)

    global best_fitness
    global best_solution

    for generation in range(iterations):
        # Calculate fitness values for the current population
        fitness_values = [fitness_function(individual) for individual in population]
        max_fitness = np.max(fitness_values)

        print(f"Generation {generation}: Max Fitness = {max_fitness}")

        # Check termination condition
        if term_condition == 0 and max_fitness == 961:
            print(f"Terminating early as Max Fitness reached 961.")
            break

        new_population = []
        for _ in range(population_size // 2 + 1):
            parent1 = population[np.random.choice(range(population_size))]
            parent2 = population[np.random.choice(range(population_size))]

            # Ensure parent2 is different from parent1
            while np.array_equal(parent2, parent1):
                parent2 = population[np.random.choice(range(population_size))]

            child1, child2 = crossover(parent1, parent2, crossover_type)

            child1 = mutation(child1, mutation_type)
            child2 = mutation(child2, mutation_type)

            new_population.extend([child1, child2])

        population = np.array(new_population)

        # Update best fitness and solution
        current_solution, current_fitness = solution_node(population)
        if current_fitness > best_fitness:
            best_solution = current_solution
            best_fitness = current_fitness

    return best_solution, best_fitness

# Example usage:
population_size = int(input("Enter population size: "))
crossover_type = int(input("Enter crossover type (0 for one-point, 1 for two-point): "))
mutation_type = int(input("Enter mutation type (0 for bit flip, 1 for swap): "))
termination_condition = int(input("Enter termination condition (0 for early termination, 1 for fixed iterations): "))

best_solution, best_fitness = genetic_algorithm(population_size, crossover_type, mutation_type, termination_condition)
print("Best solution:", best_solution)
print("Best fitness value:", best_fitness)
