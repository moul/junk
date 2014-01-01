# Pie widget
This is a simple widget that lets you render pie charts in Dashing. It looks a little bit like this:

![Screenshot](http://i.imgur.com/EUfO8pv.png)

# Usage

`dashboard.erb`:
```erb
<li data-row="2" data-col="1" data-sizex="1" data-sizey="1">
  <div data-id="bookmarks_frequency" data-view="Pie" data-title="Bookmark freq."></div>
</li>
```

`my_job.rb`:
```ruby
data = [
  { label: "Hello world", value: 16 },
  { label: "Testing", value: 34 },
]

send_event 'bookmarks_frequency', { value: data }
```

I hope you like it! If you have any questions/comments feel free to contact me at steve [at sign] stevegattuso.me