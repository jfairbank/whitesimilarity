# WhiteSimilarity

WhiteSimilarity is a Ruby gem that implements the White String Similarity Algorithm for computing the similarity between two strings. The algorithm was introduced by Simon White [here](http://www.catalysoft.com/articles/StrikeAMatch.html).

For this gem, the actual algorithm is implemented in C and maintained at [jfairbank/c_white_algorithm](https://github.com/jfairbank/c_white_similarity).

## Installation

Add this line to your application's Gemfile:

    gem 'whitesimilarity'

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install whitesimilarity

## Usage

The only method is `WhiteSimilarity.similarity` which takes two strings to compare.

```ruby
WhiteSimilarity.similarity('foo', 'bar')  # 0.0
WhiteSimilarity.similarity('dog', 'doge') # 0.8
WhiteSimilarity.similarity('dog', 'DOGE') # 0.8 - Case insensitive
WhiteSimilarity.similarity('foo', 'for')  # 0.5
```

The best use case for the similarity algorithm is to find the best matching string for another given string.

```ruby
strs = %w(foo bar quux hello world)
str = 'help'

best_match = strs.sort do |a, b|
  WhiteSimilarity.similarity(str, b) <=> WhiteSimilarity.similarity(str, a)
end.first

best_mach == 'hello'
```

## Contributing

To contribute to the algorithm implementation, please fork [jfairbank/c_white_algorithm](https://github.com/jfairbank/c_white_similarity) instead of this repo

1. Fork jfairbank/c_white_algorithm
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request
