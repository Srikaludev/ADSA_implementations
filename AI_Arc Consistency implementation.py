import queue

class ArcConsist:
    worklist = queue.Queue()  # a queue of arcs (this can be a queue or set in ac-3)

    # domains: dict of { tuples: list }
    # constraints: dict of { tuples: list }
    def __init__(self, arcs: list, domains: dict, constraints: dict):
        self.arcs = arcs
        self.domains = domains
        self.constraints = constraints

    # returns an empty \if inconsistent
    def solve(self, generate=False) -> dict:
        
        result = self.solve_helper()

        if generate:
            return result
        else:
            return_value = []

            for step in result:
                if step is None:
                    return step  
                else:
                    return_value = step

                print("Domains:", return_value[1])  

            print("\n ---------FINAL ANSWER----------\n")  # Print final answer
            return return_value[1]  # return only the final domain

    # returns each step in the algorithm, including the end result
    # each yield is a tuple containing: (edge, new domains, edges to consider)
    def solve_helper(self) -> dict:
        # setup queue with given arcs
        [self.worklist.put(arc) for arc in self.arcs]

        # yield initial domain state
        yield (None, self.domains, None)

        # continue working while worklist is not empty
        while not self.worklist.empty():
            (xi, xj) = self.worklist.get()

            if self.revise(xi, xj):
                if len(self.domains[xi]) == 0:
                    # found an inconsistency
                    yield None
                    break

                # get all of xj's neighbors
                neighbors = [neighbor for neighbor in self.arcs if neighbor[0] == xj]

                # put all neighbors into the worklist to be evaluated
                [self.worklist.put(neighbor) for neighbor in neighbors]
                
                yield ((xi, xj), self.domains, neighbors)
            else:
                yield ((xi, xj), self.domains, None)

        # yield the final return value
        yield (None, self.domains, None)

    def revise(self, xi: object, xj: object) -> bool:
        revised = False

        # get the domains for xi and xj(first arg,second arg)
        xi_domain = self.domains[xi]
        xj_domain = self.domains[xj]

        # get a list of constraints for (xi, xj)
        constraints = [constraint for constraint in self.constraints if constraint[0] == xi and constraint[1] == xj]

        for x in xi_domain[:]:
            satisfies = False  # there is a value in xjDomain that satisfies the constraint(s) between xi and xj

            for y in xj_domain:
                for constraint in constraints:
                    check_function = self.constraints[constraint]

                    # check y against x for each constraint
                    if check_function(x, y):
                        satisfies = True

            if not satisfies:
                # delete x from xiDomain
                xi_domain.remove(x)
                revised = True

        return revised


# Given Arc Constraints:
arcs = [
    ('X', 'Y'),
    ('X', 'Z'),
    ('Y', 'X'),
    ('Y', 'Z'),
    ('Z', 'X'),
    ('Z', 'Y')
]
#Initial domains:
domains = {
    'X': [1, 2, 3, 4],
    'Y': [2, 4],
    'Z': [2, 5, 8]
}


# Define constraints realtions
def equal(x, y):
    return x == y

def not_equal(x, y):
    return x != y

def greater_than_or_equal(x, y):
    return x >= y

def less_than_or_equal(x, y):
    return x <= y

constraints = {
    ('X', 'Y'): equal,
    ('Y', 'X'): equal,
    ('X', 'Z'): greater_than_or_equal,
    ('Y', 'Z'): not_equal,
    ('Z', 'X'): less_than_or_equal,
    ('Z', 'Y'): not_equal
}

print("\nThe Domains after each iteration of the AC-3 algorithm are:\n")
solver = ArcConsist(arcs, domains, constraints)
solution = solver.solve()

print("The Solution is:", solution)