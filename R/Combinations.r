########################
# Combinations Handout #
########################

# 1. Draw 5 cards out of 52 cards
choose(52, 5)

# 2. Exactly Two Kings, Two Queens, and One Ace
choose(4,2)*choose(4,2)*choose(4,1)

# 3. Exactly Two Jacks, Two Aces, and One card whose rank is different from others
choose(4,2)*choose(4,2)*choose(44,1)

# 4. Number of ways of getting Two-pair
choose(13,2)*choose(4,2)*choose(4,2)*choose(44,1)

# 5. Probability of getting Two-pair
choose(13,2)*choose(4,2)*choose(4,2)*choose(44,1)/choose(52,5)

# 6. Probability of getting three-of-a-kind
choose(13,1)*choose(4,3)*choose(12,2)*choose(4,1)*choose(4,1)/choose(52,5)

# Probability of full house
choose(13,1)*choose(4,3)*choose(12,1)*choose(4,2)/choose(52,5)

# Probability of 4 of a kind
choose(13,1)*choose(4,4)*choose(12,1)*choose(4,1)/choose(52,5)

# Probability of 1 pair
choose(13,1)*choose(4,2)*choose(48,3)/choose(52,5)

# Number of 1 pair
1098240	/choose(52,5)

bridge = choose(52,13) #bridge hand

# bridge hand (13 cards) where 5 are spades, 4 are hearts,
# 3 diamonds, and 1 club

choose(13,5)*choose(13,4)*choose(13,3)*choose(13,1)/bridge

# 5s, 4h, 2d, 2c
choose(13,5)*choose(13,4)*choose(13,2)*choose(13,2)/
  
# 5s 4h 1d 3c

  choose(13,5)*choose(13,4)*choose(13,3)*choose(13,1)/bridge

# candy hearts
choose(19,3)*choose(10,2)*choose(7,1)*choose(5,1)*choose(6,2)/choose(52,9)



