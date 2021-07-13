from libc.stdlib cimport free
from libc.string cimport strlen
from libc.stdio cimport FILE, fwrite, fprintf, fclose, stderr

cdef extern from "<stdio.h>":
    cdef FILE * open_memstream(char **, size_t *)

cdef extern from "core/intermediate.h":
    ctypedef struct NODE

cdef extern from "core/intermediate.c":
    cdef NODE *free_node(NODE *node)

cdef extern from "core/plinf.tab.h":
    cdef int yyparse()

cdef extern from "core/plinf.tab.c":
    cdef NODE *global_result

cdef extern from "core/plinf.yy.c":
    cdef void yyset_in(FILE *)
    cdef int yylex_destroy()

cdef extern from "core/tree_out.c":
    cdef void print_node(FILE *, NODE *, int)

cdef extern from "core/opcode_out.h":
    cpdef enum OPCODE "opcode":
        opcode_nop
        opcode_const_declare
        opcode_type_declare
        opcode_var_declare
        opcode_procedure_declare
        opcode_function_declare
        opcode_param_declare
        opcode_build_array_type
        opcode_load_const
        opcode_load_fast
        opcode_block_start
        opcode_block_end
        opcode_unary_negative
        opcode_unary_not
        opcode_unary_odd
        opcode_binary_power
        opcode_binary_times
        opcode_binary_divide
        opcode_binary_floor_divide
        opcode_binary_modulo
        opcode_binary_plus
        opcode_binary_minus
        opcode_binary_subscr
        opcode_binary_and
        opcode_binary_or
        opcode_binary_compare
        opcode_store_fast
        opcode_store_subscr
        opcode_jump
        opcode_jump_if_true
        opcode_jump_if_false
        opcode_call_function
        opcode_return_function

cdef extern from "core/opcode_out.c":
    cdef void opout_node(FILE *, NODE *)
    cdef void restart_opcode()


cpdef unicode get_tree(unicode code):
    cdef int result = 1
    cdef NODE *node = NULL
    code_bytes = code.encode("utf-8")
    cdef char *c_code = code_bytes
    cdef char *input_bp
    cdef char *output_bp
    cdef size_t input_size
    cdef size_t output_size
    cdef FILE *fake_input = open_memstream(&input_bp, &input_size)
    cdef FILE *fake_output = open_memstream(&output_bp, &output_size)
    yylex_destroy()
    yyset_in(fake_input)
    fwrite(c_code, sizeof(char), strlen(c_code), fake_input)

    result = yyparse()
    if result == 0:
        node = global_result
        if node is NULL:
            fprintf(stderr, "Error parsing: no result\n")
            fclose(fake_input)
            fclose(fake_output)
            free(input_bp)
            free(output_bp)
            return None
        print_node(fake_output, node, 0)
        node = free_node(node)
        while node is not NULL:
            print_node(fake_output, node, 0)
            node = free_node(node)
    else:
        fprintf(stderr, "Error parsing: code %d\n", result)
        fclose(fake_input)
        fclose(fake_output)
        free(input_bp)
        free(output_bp)
        return None

    fclose(fake_input)
    fclose(fake_output)
    free(input_bp)
    return output_bp.decode("utf-8")


cpdef unicode get_opcode(unicode code):
    cdef int result = 1
    cdef NODE *node = NULL
    code_bytes = code.encode("utf-8")
    cdef char *c_code = code_bytes
    cdef char *input_bp
    cdef char *output_bp
    cdef size_t input_size
    cdef size_t output_size
    cdef FILE *fake_input = open_memstream(&input_bp, &input_size)
    cdef FILE *fake_output = open_memstream(&output_bp, &output_size)
    yylex_destroy()
    yyset_in(fake_input)
    fwrite(c_code, sizeof(char), strlen(c_code), fake_input)

    result = yyparse()
    if result == 0:
        node = global_result
        if node is NULL:
            fprintf(stderr, "Error parsing: no result\n")
            fclose(fake_input)
            fclose(fake_output)
            free(input_bp)
            free(output_bp)
            return None
        restart_opcode()
        opout_node(fake_output, node)
        node = free_node(node)
        while node is not NULL:
            opout_node(fake_output, node)
            node = free_node(node)
    else:
        fprintf(stderr, "Error parsing: code %d\n", result)
        fclose(fake_input)
        fclose(fake_output)
        free(input_bp)
        free(output_bp)
        return None

    fclose(fake_input)
    fclose(fake_output)
    free(input_bp)
    return output_bp.decode("utf-8")
