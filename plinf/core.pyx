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
    int yyparse()

cdef extern from "core/plinf.tab.c":
    NODE *global_result

cdef extern from "core/plinf.yy.c":
    void yyset_in(FILE *)

cdef extern from "core/tree_out.c":
    cdef void print_node(FILE *, NODE *, int)

cdef extern from "core/opcode_out.h":
    cpdef enum OPCODE "opcode":
        op_nop
        op_const_declare
        op_type_declare
        op_var_declare
        op_procedure_declare
        op_function_declare
        op_assign
        op_if_then
        op_if_then_else
        op_while_do
        op_continue
        op_exit
        op_call
        op_le
        op_leq
        op_ge
        op_geq
        op_eq
        op_neq
        op_plus
        op_minus
        op_times
        op_power
        op_divide
        op_div
        op_mod
        op_odd
        op_and
        op_or
        op_not
        op_load_const
        op_load_identifier

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
