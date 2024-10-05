#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"
#include "token.h"

int check_keyword(char *p, struct token *token);
int check_identifier(char *p, struct token *token);
int check_open_parenthesis(char *p, struct token *token);
int check_close_parenthesis(char *p, struct token *token);
int check_open_brace(char *p, struct token *token);
int check_close_brace(char *p, struct token *token);
int check_constant(char *p, struct token *token);
int check_semicolon(char *p, struct token *token);

char *get_word(char *p);

char *keywords[] = {"int"};
char keywords_count = sizeof(keywords) / sizeof(*keywords);

struct token get_token(char **string) {
    char **p = string;
    struct token result = {
        .token_type = undefined,
        .value = "",
    };

    while (**p == ' ' || **p == '\n') {
        *p += 1;
    }

    if (check_keyword(*p, &result) == 0) {
        *p += strlen(result.value);
        return result;
    }

    if (check_identifier(*p, &result) == 0) {
        *p += strlen(result.value);
        return result;
    }

    if (check_open_parenthesis(*p, &result) == 0) {
        *p += strlen(result.value);
        return result;
    }

    if (check_close_parenthesis(*p, &result) == 0) {
        *p += strlen(result.value);
        return result;
    }

    if (check_open_brace(*p, &result) == 0) {
        *p += strlen(result.value);
        return result;
    }

    if (check_close_brace(*p, &result) == 0) {
        *p += strlen(result.value);
        return result;
    }

    if (check_constant(*p, &result) == 0) {
        *p += strlen(result.value);
        return result;
    }

    if (check_semicolon(*p, &result) == 0) {
        *p += strlen(result.value);
        return result;
    }

    return result;
}

struct linked_list *get_tokens(char *string) {
    struct linked_list *tokens = malloc(sizeof(struct linked_list));
    struct node *last = NULL;

    struct token token;
    while ((token = get_token(&string)).token_type != undefined) {
        struct token *tmp = malloc(sizeof(struct token));
        *tmp = token;

        struct node *temp = malloc(sizeof(struct node));
        temp->val = tmp;
        temp->next = NULL;

        if (last == NULL) {
            tokens->head = temp;
            last = temp;
        } else {
            last->next = temp;
            last = temp;
        }
    }

    return tokens;
}

char *get_word(char *string) {
    char *result = malloc(sizeof(char));
    char *p = result;
    while (isalpha(*string) || *string == '\0') {
        *p = *string;
        if (*string == '\0') {
            break;
        }
        string++;
        p++;
    }

    return result;
}

char *get_constant(char *string) {
    char *result = malloc(sizeof(char));
    char *p = result;
    while (isdigit(*string) || *string == '\0') {
        *p = *string;
        if (*string == '\0') {
            break;
        }
        string++;
        p++;
    }

    return result;
}

int check_keyword(char *p, struct token *token) {
    char *word = get_word(p);
    for (int i = 0; i < keywords_count; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            token->token_type = keyword;
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
    if (*p == ':') {
        token->token_type = semicolon;
        token->value = p;
        return 0;
    };

    return 1;
}
