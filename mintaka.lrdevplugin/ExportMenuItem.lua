local LrTasks = import 'LrTasks'
-- Access the Lightroom SDK namespaces.
local LrDialogs = import 'LrDialogs'
local LrLogger = import 'LrLogger'
local lrApplication = import 'LrApplication'
local LrShell = import 'LrShell'
local LrExportSession = import 'LrExportSession'
local LrPathUtils = import 'LrPathUtils'
local LrFileUtils = import 'LrFileUtils'


local function getSelection ()
	 local catalog = lrApplication.activeCatalog()
	 if catalog:getTargetPhoto () then
	      return catalog:getTargetPhotos ()
     else
	      return {}
          end
     end

local function showModalDialog()
	--local photo=currentPhotos[0]
    --local path= photo:getRawMetadata( 'path' )
    --local dateTimeDigitized= photo:getRawMetadata( 'dateTimeDigitized' )
    --local uuid= photo:getRawMetadata( 'uuid' )
	
	LrTasks.startAsyncTask(function()
	  local catalog = lrApplication.activeCatalog()

	  local size = 0
	  local pathes = ""
	  local photos = catalog:getMultipleSelectedOrAllPhotos()
	  local photos = getSelection()
	  
	  if next(photos) == nil then
	     LrDialogs.message("Empty")
	     return {}
      end
	  
	  local d = "xxx"
	  for k,photo in ipairs(photos) do
		  d = photo:getRawMetadata( 'path' )
		  size = size + photo:getRawMetadata("fileSize")
		  pathes = pathes .. "\n" .. photo:getRawMetadata("path")
	  end	
    
	  local out = string.format("%.1f MB%s", size / 1024 / 1024, pathes)
	  
	  local exportSettings = {
                        LR_format = "JPEG",
                        LR_export_colorSpace = "sRGB",
                        LR_export_useSubfolder = false,
                        LR_jpeg_quality = 100,
                        LR_size_resolution = 72,
                        LR_size_resolutionUnits = "inch",
                        LR_outputSharpeningOn = false,
                        LR_export_destinationType = "specificFolder",
                        LR_export_destinationPathPrefix = 'c:/dev/images/',
                        LR_collisionHandling = "skip",
						LR_extensionCase = "lowercase",
						LR_jpeg_useLimitSize = false,  
                        LR_size_doConstrain = true,  
                        LR_size_maxHeight = 300,  
                        LR_size_maxWidth = 300,  
                        LR_size_units = "pixels",  
                        LR_size_resizeType = "wh",  
						LR_tokens = {{image_originalName_number_suffix}},
      }

      local params =  {
                        photosToExport = photos,
                        exportSettings = exportSettings
                       }
      local ex = LrExportSession(params)
      
	  ex:doExportOnCurrentTask()

      for i, rendition in ex:renditions() do
        local status, other = rendition:waitForRender()
		
		local dPath = rendition.destinationPath
     --   LrDialogs.message(dPath)
		
--		local ps = LrPathUtils.child("c:/dev/images/", 'photos' )
--		LrDialogs.message(ps)
	--	LrFileUtils.copy( other, LrPathUtils.child(LrPathUtils.standardizePath(ps), 'qwerty.jpg') )
		
      end
	  
	  
--	  local f = io.open("c:/dev/test_out.txt", "w" )
--	  f:write(d)
 --     f:close()
	  
	  LrDialogs.message( "1", d, d)
	 
	   
	 -- LrTasks.execute("notepad.exe")
	end
	)
end

showModalDialog()


