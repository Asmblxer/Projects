class Number():
    def __init__(self, value):
        self.value = value

    def eval(self):
        return int(self.value)

class BinaryOp():
    def __init__(self, left, right):
        self.left = left
        self.right = right

class Sum(BinaryOp):
    def eval(self):
        return self.left.eval() + self.right.eval()

class Sub(BinaryOp):
    def eval(self):
        return self.left.eval() - self.right.eval()

class Mul(BinaryOp):
    def eval(self):
        return self.left.eval() * self.right.eval()

class Div(BinaryOp):
    def eval(self):
        return self.left.eval() / self.right.eval()
    
class LessThan(BinaryOp):
    def eval(self):
        return self.left.eval() < self.right.eval()
    
class LessThanEqual(BinaryOp):
    def eval(self):
        return self.left.eval() <= self.right.eval()

class Equals(BinaryOp):
    def eval(self):
        return self.left.eval() == self.right.eval()

class GreaterThan(BinaryOp):
    def eval(self):
        return self.left.eval() > self.right.eval()

class GreaterThanEqual(BinaryOp):
    def eval(self):
        return self.left.eval() >= self.right.eval()
    
class NotEquals(BinaryOp):
    def eval(self):
        return self.left.eval() != self.right.eval()
    
class And(BinaryOp):
        def eval(self):
            return self.left.eval() and self.right.eval()
        
class Or(BinaryOp):
    def eval(self):
        return self.left.eval() or self.right.eval()

class If():
    def __init__(self, condition, if_block, else_block=None):
        self.condition = condition
        self.if_block = if_block
        self.else_block = else_block

    def eval(self):
        condition_value = self.condition.eval()
        if condition_value:
            return self.if_block.eval()
        elif self.else_block:
            return self.else_block.eval()
        else:
            return None

class Output():
    def __init__(self, value):
        self.value = value

    def eval(self):
        print(self.value.eval())



from rply import LexerGenerator, ParserGenerator
class Lexer():
    def __init__(self):
        self.lexer = LexerGenerator()

    def _add_tokens(self):
        # Parenthesis
        self.lexer.add('OPEN_PAREN', r'\(')
        self.lexer.add('CLOSE_PAREN', r'\)')
        # Semi Colon
        self.lexer.add('SEMI_COLON', r'\;')
        # Operators
        self.lexer.add('SUM', r'\+')
        self.lexer.add('SUB', r'\-')
        self.lexer.add('MUL', r'\*')
        self.lexer.add('DIV', r'\/')
        self.lexer.add('LESS_THAN', r'\<')
        self.lexer.add('LESS_THAN_EQUAL', r'\<=')
        self.lexer.add('EQUALS', r'==')
        self.lexer.add('GREATER_THAN', r'\>')
        self.lexer.add('GREATER_THAN_EQUAL', r'\>=')
        self.lexer.add('NOT_EQUALS', r'!=')
        self.lexer.add('AND', r'&&')
        self.lexer.add('OR', r'\|\|')
        # Output
        self.lexer.add('OUTPUT', r'out')
        # Number
        self.lexer.add('NUMBER', r'\d+')
        # If statement
        self.lexer.add('IF', r'if')
        #Else
        self.lexer.add('ELSE', r'else')
        # Ignore spaces
        self.lexer.ignore('\s+')

    def get_lexer(self):
        self._add_tokens()
        return self.lexer.build()
    

class Parser():
    def __init__(self):
        self.pg = ParserGenerator(
            # A list of all token names accepted by the parser.
            ['NUMBER', 'OUTPUT', 'OPEN_PAREN', 'CLOSE_PAREN',
             'SEMI_COLON', 'SUM', 'SUB', 'MUL', 'DIV', 'LESS_THAN', 'LESS_THAN_EQUAL', 'EQUALS', 'GREATER_THAN', 'GREATER_THAN_EQUAL', 'NOT_EQUALS', 'AND', 'OR', 'IF', 'ELSE'],
        )

    def parse(self):
        @self.pg.production('program : OUTPUT OPEN_PAREN expression CLOSE_PAREN SEMI_COLON')
        def program(p):
            return Output(p[2])

        @self.pg.production('expression : expression SUM expression')
        @self.pg.production('expression : expression SUB expression')

        @self.pg.production('expression : expression MUL expression')
        @self.pg.production('expression : expression DIV expression')

        @self.pg.production('expression : expression LESS_THAN expression')
        @self.pg.production('expression : expression LESS_THAN_EQUAL expression')
        @self.pg.production('expression : expression EQUALS expression')
        @self.pg.production('expression : expression GREATER_THAN expression')
        @self.pg.production('expression : expression GREATER_THAN_EQUAL expression')
        @self.pg.production('expression : expression NOT_EQUALS expression')

        @self.pg.production('expression : expression AND expression')
        @self.pg.production('expression : expression OR expression')


        def expression(p):
            left = p[0]
            right = p[2]
            operator = p[1]
            if operator.gettokentype() == 'SUM':
                return Sum(left, right)
            elif operator.gettokentype() == 'SUB':
                return Sub(left, right)
            elif operator.gettokentype() == 'MUL':
                return Mul(left, right)
            elif operator.gettokentype() == 'DIV':
                return Div(left, right)
            elif operator.gettokentype() == 'LESS_THAN':
                return LessThan(left, right)
            elif operator.gettokentype() == 'LESS_THAN_EQUAL':
                return LessThanEqual(left, right)
            elif operator.gettokentype() == 'EQUALS':
                return Equals(left, right)
            elif operator.gettokentype() == 'GREATER_THAN':
                return GreaterThan(left, right)
            elif operator.gettokentype() == 'GREATER_THAN_EQUAL':
                return GreaterThanEqual(left, right)
            elif operator.gettokentype() == 'NOT_EQUALS':
                return NotEquals(left, right)
            elif operator.gettokentype() == 'AND':
                return And(left, right)
            elif operator.gettokentype() == 'OR':
                return Or(left, right)
            else:
                raise ValueError(operator)

        @self.pg.production('expression : NUMBER')
        def number(p):
            return Number(p[0].value)
        
        @self.pg.production('block : program')
        def block(p):
            return p[0]
        
        @self.pg.production('condition : expression')
        def condition_single_expr(p):  # New production rule
            return p[0]

        @self.pg.production('condition : OPEN_PAREN expression CLOSE_PAREN')
        def condition_parenthesized(p):  # Existing production rule
            return p[1]

        @self.pg.production('statement : IF OPEN_PAREN condition CLOSE_PAREN block')
        @self.pg.production('statement : IF OPEN_PAREN condition CLOSE_PAREN block ELSE block')
        def statement(p):
            condition = p[2]
            if_block = p[4]
            else_block = p[6] if len(p) > 6 else None
            return If(condition, if_block, else_block)

        @self.pg.error
        def error_handle(token):
            raise ValueError(token)

    def get_parser(self):
        return self.pg.build()
    
text_input = """

out(1 + 2 * 3);

"""

lexer = Lexer().get_lexer()
tokens = lexer.lex(text_input)
lexems = lexer.lex(text_input)

def print_lexems(lexems):
    print("Lexems:")
    print("--------")
    for token in lexems:
        print(f"Token: {token.gettokentype()}, Value: {token.getstr()}")
    print("--------")

pg = Parser()
pg.parse()
parser = pg.get_parser()
parser.parse(tokens).eval()
print_lexems(lexems)



def calculate_first(grammar):
    first = {}
    for production in grammar:
        non_terminal = production[0]
        if non_terminal not in first:
            first[non_terminal] = set()
        if production[1][0] not in first:
            first[production[1][0]] = set()
        if production[1][0] != non_terminal:
            first[non_terminal].add(production[1][0])
    return first

def calculate_follow(grammar, first):
    follow = {}
    for production in grammar:
        non_terminal = production[0]
        if non_terminal not in follow:
            follow[non_terminal] = set()
        for i in range(1, len(production[1])):
            if production[1][i] in first:
                follow[non_terminal].update(first[production[1][i]])
            if production[1][i] not in first:
                if production[1][i] not in follow:
                    follow[production[1][i]] = set()
                follow[non_terminal].update(follow[production[1][i]])  # Update follow set for non-terminals not in the first set
    return follow

grammar = [
    ('program', ['OUTPUT', 'OPEN_PAREN', 'expression', 'CLOSE_PAREN', 'SEMI_COLON']),
    ('expression', ['expression', 'SUM', 'expression']),
    ('expression', ['expression', 'SUB', 'expression']),
    ('expression', ['expression', 'MUL', 'expression']),
    ('expression', ['expression', 'DIV', 'expression']),
    ('expression', ['expression', 'LESS_THAN', 'expression']),
    ('expression', ['expression', 'LESS_THAN_EQUAL', 'expression']),
    ('expression', ['expression', 'EQUALS', 'expression']),
    ('expression', ['expression', 'GREATER_THAN', 'expression']),
    ('expression', ['expression', 'GREATER_THAN_EQUAL', 'expression']),
    ('expression', ['expression', 'NOT_EQUALS', 'expression']),
    ('expression', ['expression', 'AND', 'expression']),
    ('expression', ['expression', 'OR', 'expression']),
    ('expression', ['NUMBER']),
    ('block', ['program']),
    ('condition', ['expression']),
    ('condition', ['OPEN_PAREN', 'expression', 'CLOSE_PAREN']),
    ('statement', ['IF', 'OPEN_PAREN', 'condition', 'CLOSE_PAREN', 'block']),
    ('statement', ['IF', 'OPEN_PAREN', 'condition', 'CLOSE_PAREN', 'block', 'ELSE', 'block']),
    

]

first = calculate_first(grammar)
follow = calculate_follow(grammar, first)

print("First sets:")
print("-----------")
for non_terminal, first_set in first.items():
    print(f"{non_terminal}: {first_set}")
print("-----------")

print("Follow sets:")
print("------------")
for non_terminal, follow_set in follow.items():
    print(f"{non_terminal}: {follow_set}")
print("------------")