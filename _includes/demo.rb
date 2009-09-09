require 'rubygems'
require 'joker'


wild = Wildcard['Fairy?ake*']

wild =~ 'Fairycake'                     #=> true
wild =~ 'Fairyfakes'                    #=> true
wild =~ 'Fairylake is a cool place'     #=> true

wild =~ 'Dairycake'                     #=> false
wild =~ 'Fairysteakes'                  #=> false
wild =~ 'fairycake'                     #=> false

wildi = Wildcard['Fairy?ake*\?', true]

wildi =~ 'FairyCake?'                   #=> true
wildi =~ 'fairyfakes?'                  #=> true
wildi =~ 'FairyLake IS A COOL Place?'   #=> true

Wildcard.quote('*?\\')                  #=> '\\*\\?\\\\'

