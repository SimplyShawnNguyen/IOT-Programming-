import { getRedisClient } from '~/server/redis'

export default defineEventHandler(async () => {
    const redis = await getRedisClient()

    const currentState = await redis.get('fanState') === '1'

    await redis.set('fanState', !currentState ? '1' : '0')

    return {
        ok: true,
    }
})
