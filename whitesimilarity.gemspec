# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'whitesimilarity/version'

Gem::Specification.new do |spec|
  spec.name          = 'whitesimilarity'
  spec.version       = WhiteSimilarity::VERSION
  spec.authors       = ['Jeremy Fairbank']
  spec.email         = ['elpapapollo@gmail.com']
  spec.description   = %q{An implementation of the White Similarity Algorithm in C}
  spec.summary       = %q{White Similarity Algorithm}
  spec.homepage      = 'https://github.com/jfairbank/whitesimilarity'
  spec.license       = 'MIT'

  spec.files         = `git ls-files`.split($/)
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ['lib']
  spec.extensions    = ['ext/whitesimilarity/extconf.rb']

  spec.add_development_dependency 'bundler', '~> 1.3'
  spec.add_development_dependency 'rake'
end
