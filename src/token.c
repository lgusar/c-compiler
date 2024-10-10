#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"
#include "token.h"

int clear_whitespace(char **p);
int check_single_line_comment(char **p);
int check_multi_line_comment(char **p);
int check_keyword(char *p, struct token *token);
int check_identifier(char *p, struct token *token);
int check_open_parenthesis(char *p, struct token *token);
int check_close_parenthesis(char *p, struct token *token);
int check_open_brace(char *p, struct token *token);
int check_close_brace(char *p, struct token *token);
int check_constant(char *p, struct token *token);
int check_semicolon(char *p, struct token *token);

char *get_word(char *p);

char *keywords[] = {"int", "return", "void"};
char keywords_count = sizeof(keywords) / sizeof(*keywords);

int get_token(char **string, struct token *result) {
    char **p = string;

    result->token_type = undefined;

    if (clear_whitespace(p) == 0) {
        result = NULL;
        return 0;
    }

    if (check_single_line_comment(p) == 0) {
        result = NULL;
        return 0;
    }

    if (check_multi_line_comment(p) == 0) {
        result = NULL;
        return 0;
    }

    if (**p == EOF || **p == '\0') {
        return 1;
    }

    if (check_keyword(*p, result) == 0) {
        *p += strlen(result->value);
        return 0;
    }

    if (check_identifier(*p, result) == 0) {
        *p += strlen(result->value);
        return 0;
    }

    if (check_open_parenthesis(*p, result) == 0) {
        *p += strlen(result->value);
        return 0;
    }

    if (check_close_parenthesis(*p, result) == 0) {
        *p += strlen(result->value);
        return 0;
    }

    if (check_open_brace(*p, result) == 0) {
        *p += strlen(result->value);
        return 0;
    }

    if (check_close_brace(*p, result) == 0) {
        *p += strlen(result->value);
        return 0;
    }

    if (check_constant(*p, result) == 0) {
        *p += strlen(result->value);
        return 0;
    }

    if (check_semicolon(*p, result) == 0) {
        *p += strlen(result->value);
        return 0;
    }

    result->token_type = undefined;

    fprintf(stderr, "unrecognized token\n");
    return -1;
}

int get_tokens(char *string, struct linked_list *tokens) {
    struct token token;
    int status;
    while ((status = get_token(&string, &token)) != 1) {
        if (status == -1) {
            fprintf(stderr, "get_token failed\n");
            return 1;
        }

        if (token.token_type == undefined) {
            continue;
        }

        struct token *tmp = malloc(sizeof(struct token));
        *tmp = token;

        linked_list_add(tokens, tmp);
    }

    return 0;
}

int clear_whitespace(char **p) {
    if (**p == ' ' || **p == '\n' || **p == '\t') {
        while (**p == ' ' || **p == '\n' || **p == '\t') {
            *p += 1;
        }

        return 0;
    }

    return 1;
}

int check_single_line_comment(char **p) {
    if (strncmp(*p, "//", strlen("//")) == 0) {
        while (**p != '\n' && **p != EOF && **p != '\0') {
            *p += 1;
        }

        return 0;
    }

    return 1;
}

int check_multi_line_comment(char **p) {
    if (strncmp(*p, "/*", strlen("/*")) == 0) {
        while (**p != EOF && **p != '\0') {
            *p += 1;
            if (**p == '*' && *(*p + 1) == '/') {
                *p += 2;
                break;
            }
        }

        return 0;
    }

    return 1;
}

char *get_word(char *string) {
    int n = 0;
    char *p = string;
    while (isalpha(*p) || *p == '\0') {
        n++;
        p++;
    }

    char *result = malloc(sizeof(char) * (n + 1));
    strncpy(result, string, n);
    result[n] = '\0';

    return result;
}

char *get_constant(char *string) {
    int n = 0;
    char *p = string;
    while (isdigit(*p) || *p == '\0') {
        n++;
        p++;
    }

    if (isalpha(*p)) {
        return NULL;
    }

    char *result = malloc(sizeof(char) * (n + 1));
    strncpy(result, string, n);
    result[n] = '\0';

    return result;
}

int check_keyword(char *p, struct token *token) {
    char *word = get_word(p);
    for (int i = 0; i < keywords_count; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            /* i corresponds to correct keyword token_type*/
            token->token_type = i;
            token->value = word;

            return 0;
        }
    }

    return 1;
}

int check_identifier(char *p, struct token *token) {
    char *word = get_word(p);
    if (strlen(word) != 0) {
        token->token_type = identifier;
        token->value = word;
        return 0;
    }

    return 1;
}

int check_open_parenthesis(char *p, struct token *token) {
    if (*p == '(') {
        token->token_type = open_parenthesis;
        token->value = "(";
        return 0;
    };

    return 1;
}

int check_close_parenthesis(char *p, struct token *token) {
    if (*p == ')') {
        token->token_type = close_parenthesis;
        token->value = ")";
        return 0;
    };

    return 1;
}

int check_open_brace(char *p, struct token *token) {
    if (*p == '{') {
        token->token_type = open_brace;
        token->value = "{";
        return 0;
    };

    return 1;
}

int check_close_brace(char *p, struct token *token) {
    if (*p == '}') {
        token->token_type = close_brace;
        token->value = "}";
        return 0;
    };

    return 1;
}

int check_constant(char *p, struct token *token) {
    char *value = get_constant(p);
    if (strlen(value) != 0) {
        token->token_type = constant;
        token->value = value;
        return 0;
    }

    return 1;
}

int check_semicolon(char *p, struct token *token) {
    if (*p == ';') {
        token->token_type = semicolon;
        token->value = p;
        return 0;
    };

    return 1;
}

char *get_token_type(enum token_type token_type) {
    switch(token_type) {
        case k_int: return "int"; 
        case k_return: return "return";
        case k_void: return "void";
        case identifier: return "identifier";
        case open_parenthesis: return "open_parenthesis";
        case close_parenthesis: return "close_parenthesis";
        case open_brace: return "open_brace"; 
        case close_brace: return "close_brace"; 
        case constant: return "constant";
        case semicolon: return "semicolon";
        case undefined: return "undefined";
    }

    return "";
}
