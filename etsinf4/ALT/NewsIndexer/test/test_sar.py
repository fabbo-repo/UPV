import pickle
import unittest
import os, sys
currentdir = os.path.dirname(os.path.realpath(__file__))
parentdir = os.path.dirname(currentdir)
sys.path.append(parentdir)
from lib import Core

class SearcherTest(unittest.TestCase):
    def __init__(self, *args, **kwargs):
        unittest.TestCase.__init__(self, *args, **kwargs)
    
    def test_basic_parentesis(self):
        with open('../index/2015_index_full.bin', 'rb') as fh:
            searcher = pickle.load(fh)
        with open("test_sar.txt", encoding='utf-8') as fh:
            lines = fh.read().split('\n')
            for line in lines:
                if len(line) > 0 and not line.startswith('#'):
                    aux = line.split('  ')
                    query, reference = aux[0], aux[1]
                    reference = int(reference)
                    result = searcher.solve_and_count(query)
                    self.assertEqual(result, reference)
                else:
                    print(line)
            
if __name__ == "__main__":
    unittest.main()