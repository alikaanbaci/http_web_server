/*
 * author: alikaanbaci
 * created date: Sunday August 4th 2019
 */

#include <CUnit/Basic.h>

 int test_example(){
     CU_ASSERT_EQUAL(1, 1);
 } 

int main(){
    CU_pSuite pSuite = NULL;
    
    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry()){
       return CU_get_error();
    }

    /* add a suite to the registry */
    //pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
    pSuite = CU_add_suite("suite_1", NULL, NULL);
    if (NULL == pSuite) {
       CU_cleanup_registry();
       return CU_get_error();
    }

    /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */

   if ((NULL == CU_add_test(pSuite, "test of compare", test_example)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}

