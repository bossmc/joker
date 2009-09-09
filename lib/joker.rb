#
# Joker is a simple wildcard implementation that works much like Regexps.
#

#
# Implements wildcards for Ruby. Modeled after the Regexp class.
#
# This implementation supports the following special characters:
#
# - '?'   matches a single character
# - '*'   matches any number of characters, including 0
# - '\*'  matches a literal '*'
# - '\?'  matches a literal '?'
# - '\\'  matches a literal '\'
#
# NOTE that '\a' will match the literal string '\a'.
#
#   wild = Wildcard['Fairy?ake*']
#   wild =~ 'Fairycake'                     #=> true
#   wild =~ 'Fairyfakes are mean'           #=> true
#   wild =~ 'Fairysteakes are delicious'    #=> false
#
# Also there is a case sensitivity flag. By default it is set to true,
# but it can be turned off at construction time:
#
#   wild = Wildcard['Fairy?ake*', true]
#   wild =~ 'Fairycake'
#   wild =~ 'fairyCAKE'
#   wild =~ 'FaIrYfAkEs, the Movie'
#
# Furthermore, any given Wildcard expression must match the whole string:
#
#   wild = Wildcard['Fairy?ake']
#   wild =~ 'some Fairycake'                #=> false
#   wild =~ 'Fairycake is good for you'     #=> false
#
class Wildcard

    #
    # Boolean. Determines case sensitivity of the Wildcard.
    #
    # If this is true, the Wildcard will ignore case.
    #
    attr_reader :casefold

    #
    # The string from which the Wildcard was constructed.
    #
    attr_reader :source

    #
    # Creates a new Wildcard from the given string.
    # If casefold is true, the Wildcard will ignore case.
    #
    def initialize( wildcard_string, casefold = false )
        @source   = wildcard_string
        @casefold = casefold
        @regexp   =
            if casefold then Regexp.new(compile, Regexp::IGNORECASE)
            else             Regexp.new(compile)
            end
    end

    class << self

        #
        # Returns a new string with any characters escaped that would have
        # special meaning in a Wildcard.
        #
        def quote( string )
            string.gsub(%r{[\\?*]}) { |char| "\\#{char}" }
        end

        alias_method :[], :new
        alias_method :compile, :new
        alias_method :escape, :quote

    end

    def inspect
        %{Wildcard[#{@wild.inspect}]#{@casefold ? 'i' : ''}}
    end

    #
    # Matches the wildcard against $_:
    #
    #   $_ = 'I love fairycakes'
    #   ~Wildcard['*fairy*']        #=> true
    #
    def ~
        self =~ $_
    end

    #
    # Matches the Wildcard against the given string.
    #
    # NOTE: Since a wildcard has to match the whole string,
    # this method only returns true or false, not the position
    # of the match.
    #
    #   Wildcard['*fairy*'] =~ 'I love fairycake'   #=> true
    #   'I love fairycake' =~ Wildcard['*dairy*']   #=> false
    #
    def =~( string )
        !!(@regexp =~ string)
    end

    #
    # The case operator. Allows you to use Wildcards in case
    # expressions:
    #
    #   case 'I love fairycake'
    #   when Wildcard['*fairy*'] then puts 'fairy!'
    #   else puts 'no fairy...'
    #   end
    #
    def ===( object )
        !!(@regexp =~ object)
    end

    #
    # Compares to Wildcards for equality.
    #
    # Two wildcards are equal, if they were constructed from the
    # same string and have the same #casefold?().
    #
    def eql?( that )
        return false unless that.is_a?(Wildcard)
        @source == that.source && @casefold == that.casefold
    end

    alias_method :==, :eql?
    alias_method :casefold?, :casefold

    private

    #
    # Converts the wildcard string into a Regexp.
    # A simple parser, I just threw it in there, no
    # optimizations.
    #
    def compile
        ptr = 0
        compiled = '^'
        while ptr < @source.length
            snip = @source[ptr..ptr]
            case snip
            when '\\'
                lookahead = @source[ptr+1..ptr+1]
                case snip
                when '\\\\', '\\?', '\\*'
                    compiled << snip << lookahead
                else
                    compiled << Regexp.quote(lookahead)
                end
                ptr += 1
            when '?' then compiled << '.'
            when '*' then compiled << '.*'
            else          compiled << Regexp.quote(snip)
            end
            ptr += 1
        end
        compiled + '$'
    end

end

