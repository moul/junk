crypto =   require 'crypto'
tar =      require 'tar'
zlib =     require 'zlib'
combine =  require 'stream-combiner'
through =  require 'through'


decrypter = crypto.createDecipher process.argv[2], process.argv[3]


gunziper = zlib.createGunzip()


untarer = tar.Parse()
untarer.on 'entry', (entry) ->
  return unless entry.type is 'File'

  hasher = crypto.createHash 'md5', encoding: 'hex'

  formatter_end = ->
    @queue " #{entry.path}\n"
  formatter = through null, formatter_end

  entry.pipe(hasher).pipe(formatter).pipe(process.stdout)


combined = combine decrypter, gunziper, untarer


process.stdin.pipe(combined)
