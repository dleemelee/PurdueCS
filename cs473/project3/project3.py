import csv
import json
import math


def cos(ur1, ur2):
  sumxx, sumxy, sumyy = 0.0, 0.0, 0.0
  count = 0
  for dish in ur1:
    if dish in ur2:
      sumxx += ur1[dish] * ur1[dish]
      sumyy += ur2[dish] * ur2[dish]
      sumxy += ur1[dish] * ur2[dish]
      count+=1
  #print sumxy
  #print sumxx
  #print sumyy
  if count == 0:
    return 0;
  return sumxy/(math.sqrt(sumxx)*math.sqrt(sumyy))

def part1(dishID, userID, user_ratings):
  exists = 0
  rating = 0
  if str(userID) in user_ratings:
    ratings = user_ratings[str(userID)]
    for i in range(0, len(ratings)):
      if dishID == ratings[i][0]:
        exists = 1
        rating =  ratings[i][1]
        return rating, exists
  if exists == 0:
    total = 0.0
    user_curr = {}
    curr_avg = 0.0
    num = 0.0
    den = 0.0

    ratings = user_ratings[str(userID)]
    for i in range(0, len(ratings)):
      user_curr[ratings[i][0]] = ratings[i][1]
      curr_avg += ratings[i][1]
    curr_avg/=len(ratings)

    for user in user_ratings:
      if user != str(userID):
        ratings = user_ratings[user]
        avg = 0.0
        userX = {}
        for i in range(0, len(ratings)):
          userX[ratings[i][0]] = ratings[i][1]
          avg += ratings[i][1]
        if dishID in userX :
          sim = cos(user_curr,userX)
          avg/=len(ratings)
          num += (userX[dishID]-avg)*sim
          den += sim
          #print sim
          #print avg
    #print(str(curr_avg) + " " + str(num) + " " + str(den))
    if den == 0:
      return 0 , exists
    rating=(curr_avg+(num/den))
  return rating, exists

def part2(userID, ings, ing_v, ing_mat, dishes, user_ratings):
  for i in range(0,len(ings)):
    for j in range(0, len(ing_v)):
      if ings[i] == ing_v[j]:
        ings[i] = j
  #print ings
  
  foods = {}
  for i in range(0,len(ing_mat)):
    x = 0
    for j in range(0,len(ings)):
      #print ing_mat[i][ings[j]],
      if ing_mat[i][ings[j]]==str(0):
        x=x-1
    #print x
    if x == 0:
      foods[dishes[i]] = i
  if len(foods) == 0:
    return "none", 0
  scores = {}
  for food in foods:
    rate, ex = part1(userID, foods[food], user_ratings)
    scores[food] = [rate, ex]
  max = -100
  ret = "none"
  for food in foods:
    if scores[food][0] > max:
      ret = food
      max = scores[food][0]
  return ret, scores[food][1]


if __name__ == '__main__':
  #reading 
  ing_v = [] #vector with format of csv
  ing_mat = [] #vector with dishid, dishname, and 0 if ing exists, 1 if not
  dishes = [] #dish names in dishid elements
  user_ratings = json.load(open('./user_ratings.json', 'r'))

  test_ratings = {"1": [[1,5],[2,3],[3,3],[4,4]], "2": [[0,4],[1,1],[3,3],[4,2]], "3": [[0,1],[2,3],[4,4]]}
  

  with open('dishes.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count = 0
    for row in csv_reader:
      if line_count == 0:
        column_count = 0
        for column in row:
          if column_count >= 2:
            ing_v.append(column)
          column_count+=1
        line_count+=1
      else:
        x = []
        column_count = 0
        for column in row:
          if column_count >= 2:
            x.append(column)
          elif column_count != 0:
            dishes.append(column)
          column_count+=1
        ing_mat.append(x)
        line_count+=1

#  print "ingredients vector"
#  for i in range(0, len(ing_v)):
#    print ing_v[i],
#  print

#  for i in range(0, len(ing_mat)):
#    for y in range(0,(len(ing_mat[0]))):
#      print ing_mat[i][y],
#    print

#  for i in range(0, len(dishes)):
#    print dishes[i]
#  print

#  for user in user_ratings:
#    print user,
#    for rating in user_ratings[user]:
#      print rating[0],
#      print rating[1], 
#    print

 
#  print "part1"
#  dishID = input("Enter dish ID: ");
#  userID_1 = input("Enter user ID: ");

#  rate, exists = part1(dishID, userID_1, user_ratings)
  #rate, exists = part1(1,3,test_ratings)
#  print "Rating: "+ str(rate),  
#  if exists == 0:
#    print "(estimated)"
#  else:
#    print "(existing)"

  print "part2"
  userID_2 = input("Enter user ID: ");
  k = input("Enter number of ingredients: ");
  x = [];
  for i in range(0,k):
    input = raw_input("Enter Item " + str(i+1) + ": ");
    x.append(input);

  newDish,ex  = part2(userID_2, x, ing_v, ing_mat, dishes, user_ratings)
  if newDish == "none":
    print "No dish with specified ingredients"
  elif ex == 0:
    print "Suggested dish:"
    print newDish
  elif ex == 1:
    print "No new dish with specified ingredients"
    print newDish
