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
    
    def test_leven_1(self):
        with open('../index/2015_index.bin', 'rb') as fh:
            searcher = pickle.load(fh)
        searcher.set_threshold(1)
        searcher.set_distance('levenshtein')
        with open("test_alt.txt", encoding='utf-8') as fh:
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
    
    def test_leven_2(self):
        with open('../index/2015_index.bin', 'rb') as fh:
            searcher = pickle.load(fh)
        searcher.set_threshold(2)
        searcher.set_distance('levenshtein')
        with open("test_alt.txt", encoding='utf-8') as fh:
            lines = fh.read().split('\n')
            for line in lines:
                if len(line) > 0 and not line.startswith('#'):
                    aux = line.split('  ')
                    query, reference = aux[0], aux[2]
                    reference = int(reference)
                    result = searcher.solve_and_count(query)
                    self.assertEqual(result, reference)
                else:
                    print(line)

    def test_leven_3(self):
        with open('../index/2015_index.bin', 'rb') as fh:
            searcher = pickle.load(fh)
        searcher.set_threshold(3)
        searcher.set_distance('levenshtein')
        with open("test_alt.txt", encoding='utf-8') as fh:
            lines = fh.read().split('\n')
            for line in lines:
                if len(line) > 0 and not line.startswith('#'):
                    aux = line.split('  ')
                    query, reference = aux[0], aux[3]
                    reference = int(reference)
                    result = searcher.solve_and_count(query)
                    self.assertEqual(result, reference)
                else:
                    print(line)
                    
    def test_res_leven_1(self):
        with open('../index/2015_index.bin', 'rb') as fh:
            searcher = pickle.load(fh)
        searcher.set_threshold(1)
        searcher.set_distance('restricted')
        with open("test_alt.txt", encoding='utf-8') as fh:
            lines = fh.read().split('\n')
            for line in lines:
                if len(line) > 0 and not line.startswith('#'):
                    aux = line.split('  ')
                    query, reference = aux[0], aux[4]
                    reference = int(reference)
                    result = searcher.solve_and_count(query)
                    self.assertEqual(result, reference)
                else:
                    print(line)
                    
    def test_res_leven_2(self):
        with open('../index/2015_index.bin', 'rb') as fh:
            searcher = pickle.load(fh)
        searcher.set_threshold(2)
        searcher.set_distance('restricted')
        with open("test_alt.txt", encoding='utf-8') as fh:
            lines = fh.read().split('\n')
            for line in lines:
                if len(line) > 0 and not line.startswith('#'):
                    aux = line.split('  ')
                    query, reference = aux[0], aux[5]
                    reference = int(reference)
                    result = searcher.solve_and_count(query)
                    self.assertEqual(result, reference)
                else:
                    print(line)
                    
    def test_res_leven_3(self):
        with open('../index/2015_index.bin', 'rb') as fh:
            searcher = pickle.load(fh)
        searcher.set_threshold(3)
        searcher.set_distance('restricted')
        with open("test_alt.txt", encoding='utf-8') as fh:
            lines = fh.read().split('\n')
            for line in lines:
                if len(line) > 0 and not line.startswith('#'):
                    aux = line.split('  ')
                    query, reference = aux[0], aux[6]
                    reference = int(reference)
                    result = searcher.solve_and_count(query)
                    self.assertEqual(result, reference)
                else:
                    print(line)
                    
    def test_inter_1(self):
        with open('../index/2015_index.bin', 'rb') as fh:
            searcher = pickle.load(fh)
        searcher.set_threshold(1)
        searcher.set_distance('intermediate')
        with open("test_alt.txt", encoding='utf-8') as fh:
            lines = fh.read().split('\n')
            for line in lines:
                if len(line) > 0 and not line.startswith('#'):
                    aux = line.split('  ')
                    query, reference = aux[0], aux[7]
                    reference = int(reference)
                    result = searcher.solve_and_count(query)
                    self.assertEqual(result, reference)
                else:
                    print(line)
                    
    def test_inter_2(self):
        with open('../index/2015_index.bin', 'rb') as fh:
            searcher = pickle.load(fh)
        searcher.set_threshold(2)
        searcher.set_distance('intermediate')
        with open("test_alt.txt", encoding='utf-8') as fh:
            lines = fh.read().split('\n')
            for line in lines:
                if len(line) > 0 and not line.startswith('#'):
                    aux = line.split('  ')
                    query, reference = aux[0], aux[8]
                    reference = int(reference)
                    result = searcher.solve_and_count(query)
                    self.assertEqual(result, reference)
                else:
                    print(line)

    def test_inter_3(self):
        with open('../index/2015_index.bin', 'rb') as fh:
            searcher = pickle.load(fh)
        searcher.set_threshold(3)
        searcher.set_distance('intermediate')
        with open("test_alt.txt", encoding='utf-8') as fh:
            lines = fh.read().split('\n')
            for line in lines:
                if len(line) > 0 and not line.startswith('#'):
                    aux = line.split('  ')
                    query, reference = aux[0], aux[9]
                    reference = int(reference)
                    result = searcher.solve_and_count(query)
                    self.assertEqual(result, reference)
                else:
                    print(line)
            
if __name__ == "__main__":
    unittest.main()