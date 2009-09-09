require 'rake/clean'

CLEAN.include '_site'

task :test => [:clean] do
    sh 'jekyll --server 4567 --pygments'
end

task :rdoc do
    sh 'git checkout master'
    sh 'rake rdoc'
    sh 'mv rdoc __rdoc'
    sh 'git checkout gh-pages'
    sh 'rm -r rdoc' if File.exist?('rdoc')
    sh 'mv __rdoc rdoc'
    sh 'git add rdoc'
    sh 'git commit -a -m "updated rdoc"'
end

