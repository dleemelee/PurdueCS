import json
import numpy as np

if __name__ == '__main__':
  res_hits = json.load(open('hub_auth_scores.json', 'r'))
  res_pr = json.load(open('pagerank_scores.json', 'r'))

  max_hub = 0
  min_hub = 1
  median_hub = 0
  std_hub = 0
  i = 0
  hubs = np.ones(shape=(500))

  for tup in res_hits['hub_scores'][:500]:
    if tup[1] > max_hub:
      max_hub = tup[1]
    if tup[1] < min_hub:
      min_hub = tup[1]
    if i == 249 or i == 250:
      median_hub+=tup[1]
    hubs[i] = tup[1]
    i+=1
    


